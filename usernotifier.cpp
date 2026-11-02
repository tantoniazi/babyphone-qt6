#include "usernotifier.h"

#include <QDebug>
#include <QProcess>

UserNotifier::UserNotifier(const Settings *settings, CallMonitor *callMonitor, QObject *parent)
    : QObject(parent), itsSettings(settings), itsCallMonitor(callMonitor)
{
}

bool UserNotifier::Notify()
{
    itsCallCounterInvoke++;
    qDebug() << "UserNotifier: Notify - initiating call";
    if (itsCallMonitor) {
        itsCallMonitor->takeCall();
        return true;
    }
    return false;
}

void UserNotifier::notifySMS(const QString &phoneNumber)
{
    Q_UNUSED(phoneNumber)
    qDebug() << "UserNotifier: notifySMS - sending SMS notification";
    if (!itsSettings->itsUserNotifyScript.isEmpty()) {
        QProcess::startDetached(itsSettings->itsUserNotifyScript);
    }
}
