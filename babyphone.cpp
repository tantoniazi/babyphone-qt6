#include "babyphone.h"

#include <QDebug>

Babyphone::Babyphone(const Settings *settings, QObject *parent)
    : QObject(parent), itsSettings(settings)
{
    itsProfileSwitcher = new ProfileSwitcher(itsSettings, this);
    itsState = STATE_OFF;
    itsNotificationPending = false;

    itsAudioMonitor = new AudioMonitor(itsSettings, this);
    connect(itsAudioMonitor, &AudioMonitor::update, this, &Babyphone::refreshAudioData);

    itsCallMonitor = new CallMonitor(itsSettings, this);
    connect(itsCallMonitor, &CallMonitor::callReceived, this, &Babyphone::callReceived);
    connect(itsCallMonitor, &CallMonitor::callFinished, this, &Babyphone::callFinished);

    itsUserNotifier = new UserNotifier(itsSettings, itsCallMonitor, this);
    connect(itsUserNotifier, &UserNotifier::notifyFinished, this, &Babyphone::notifyFinished);
    connect(itsCallMonitor, &CallMonitor::callStatusChanged, itsUserNotifier, [](bool){});

    startAudio();
}

void Babyphone::setState(State state)
{
    if (state == itsState)
        return;

    if (itsState == STATE_OFF) {
        itsUserNotifier->itsCallCounterInvoke = 0;
        itsUserNotifier->itsCallCounterTaken = 0;
        itsUserNotifier->itsCallCounterTimeout = 0;
    }

    qDebug() << "New application state:" << (state == STATE_OFF ? "off" :
                      state == STATE_WAITING ? "waiting" : "on");
    itsState = state;
}

QString Babyphone::getStatistics() const
{
    QString text;
    if (itsUserNotifier->itsCallCounterInvoke > 0) {
        text = tr("Notifications total: %1\nCalls taken: %2\nUnanswered or timed out: %3")
               .arg(itsUserNotifier->itsCallCounterInvoke)
               .arg(itsUserNotifier->itsCallCounterTaken)
               .arg(itsUserNotifier->itsCallCounterTimeout);
    } else {
        text = tr("No notifications took place.");
    }
    return text;
}

void Babyphone::startAudio()
{
    qDebug() << "Start audio capturing";
    bool success = itsAudioMonitor->start();
    if (!success) {
        qWarning() << "starting of audio failed, retrying later";
        QTimer::singleShot(itsSettings->AUDIO_RETRY_TIMER, this, SLOT(startAudio()));
    }
}

void Babyphone::stopAudio()
{
    qDebug() << "Stop audio capturing";
    itsAudioMonitor->stop();
}

void Babyphone::refreshAudioData(int counter, int value)
{
    emit newAudioData(counter, value);

    if ((itsState == STATE_ON) &&
        (counter > itsSettings->THRESHOLD_VALUE) &&
        (!itsCallMonitor->itsCallPending) &&
        (!itsNotificationPending))
    {
        qDebug() << "Audio threshold reached. Notifying user.";
        itsAudioMonitor->itsCounter = 0;

        if (itsUserNotifier->Notify()) {
            itsNotificationPending = true;
            QTimer::singleShot(0, this, SLOT(stopAudio()));
            emit newCallStatus(false, true);
        } else {
            emit notificationError();
        }
    }
}

void Babyphone::callReceived(QString phoneNumber)
{
    stopAudio();

    if (itsState != STATE_OFF) {
        if (itsSettings->itsHandleIncomingCalls) {
            if ((itsSettings->itsContact.IsNumberMatching(phoneNumber)) &&
                (!itsCallMonitor->itsCallPending)) {
                itsNotificationPending = true;
                itsCallMonitor->takeCall();
                emit newCallStatus(false, false);
            } else {
                if (itsCallMonitor->dropCall()) {
                    itsUserNotifier->notifySMS(phoneNumber);
                }
            }
        } else {
            itsUserNotifier->notifySMS(phoneNumber);
        }
    }
}

void Babyphone::callFinished()
{
    QTimer::singleShot(itsSettings->REFOCUS_TIMER, this, SLOT(phoneAppTimeout()));
    emit newCallStatus(true, itsNotificationPending);
}

void Babyphone::notifyFinished()
{
    if (!itsSettings->itsUserNotifyScript.isEmpty()) {
        callFinished();
    }
}

void Babyphone::phoneAppTimeout()
{
    itsNotificationPending = false;
    itsAudioMonitor->itsCounter = 0;
    startAudio();
    emit phoneApplicationFinished();
}
