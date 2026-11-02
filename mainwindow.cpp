#include "mainwindow.h"
#include <QQuickView>
#include <QQmlEngine>
#include <QQmlContext>
#include <QDebug>
#include <QDesktopServices>

MainWindow::MainWindow()
{
    itsSettings = new Settings(this);
    setupGui();

    itsActivationDelayTimer.setSingleShot(true);
    connect(&itsActivationDelayTimer, &QTimer::timeout,
            this, &MainWindow::activationTimerExpired);

    itsBabyphone = new Babyphone(itsSettings, this);
    connect(itsBabyphone, &Babyphone::newAudioData,
            this, &MainWindow::newAudioData);
    connect(itsBabyphone, &Babyphone::newCallStatus,
            this, &MainWindow::newCallStatus);
    connect(itsBabyphone, &Babyphone::phoneApplicationFinished,
            this, &MainWindow::bringWindowToFront);
    connect(itsBabyphone, &Babyphone::notificationError,
            this, &MainWindow::showNotificationError);
}

MainWindow::~MainWindow()
{
    itsSettings->Save();
}

void MainWindow::setupGui()
{
    setSource(QUrl(QStringLiteral("qrc:/main.qml")));
    connect(rootObject(), SIGNAL(requestExit()),
            this, SIGNAL(requestExit()));

    if (QObject *mainPage = rootObject()->findChild<QObject *>("mainPage")) {
        connect(mainPage, SIGNAL(dataChanged()),
                this, SLOT(dataChanged()));
        connect(mainPage, SIGNAL(changeState()),
                this, SLOT(changeState()));

        if (QObject *contact = mainPage->findChild<QObject *>("contact"))
            contact->setProperty("text", itsSettings->itsContact.GetDisplayString());

        if (QObject *aboutPage = rootObject()->findChild<QObject *>("aboutPage"))
            aboutPage->setProperty("version", itsSettings->VERSION);
    }

    setupSettingsGui();
}

void MainWindow::setupSettingsGui()
{
    if (QObject *settingsPage = rootObject()->findChild<QObject *>("settingsPage")) {
        if (QObject *obj = settingsPage->findChild<QObject *>("volume_settings"))
            obj->setProperty("value", (float)itsSettings->itsAudioAmplify);
        if (QObject *obj = settingsPage->findChild<QObject *>("duration_settings"))
            obj->setProperty("value", (float)itsSettings->itsDurationInfluence);
        if (QObject *obj = settingsPage->findChild<QObject *>("activationdelay_settings"))
            obj->setProperty("value", (float)itsSettings->itsActivationDelay);
        if (QObject *obj = settingsPage->findChild<QObject *>("recalldelay_settings"))
            obj->setProperty("value", (float)itsSettings->itsRecallTimer);
        if (QObject *obj = settingsPage->findChild<QObject *>("callsetupdelay_settings"))
            obj->setProperty("value", (float)itsSettings->itsCallSetupTimer);
        if (QObject *obj = settingsPage->findChild<QObject *>("incomingcalls_settings"))
            obj->setProperty("checked", itsSettings->itsHandleIncomingCalls);
        if (QObject *obj = settingsPage->findChild<QObject *>("sms_settings"))
            obj->setProperty("checked", itsSettings->itsSendSMS);
        if (QObject *obj = settingsPage->findChild<QObject *>("profile_settings"))
            obj->setProperty("checked", itsSettings->itsSwitchProfile);

        connect(settingsPage, SIGNAL(dataChanged()),
                this, SLOT(storeGuiSettings()));
        connect(settingsPage, SIGNAL(helpRequested()),
                this, SLOT(showHelp()));
    }
}

void MainWindow::storeGuiSettings()
{
    if (QObject *settingsPage = rootObject()->findChild<QObject *>("settingsPage")) {
        if (QObject *obj = settingsPage->findChild<QObject *>("volume_settings"))
            itsSettings->itsAudioAmplify = obj->property("value").toDouble();
        if (QObject *obj = settingsPage->findChild<QObject *>("duration_settings"))
            itsSettings->itsDurationInfluence = obj->property("value").toDouble();
        if (QObject *obj = settingsPage->findChild<QObject *>("activationdelay_settings"))
            itsSettings->itsActivationDelay = obj->property("value").toDouble();
        if (QObject *obj = settingsPage->findChild<QObject *>("recalldelay_settings"))
            itsSettings->itsRecallTimer = obj->property("value").toDouble();
        if (QObject *obj = settingsPage->findChild<QObject *>("callsetupdelay_settings"))
            itsSettings->itsCallSetupTimer = obj->property("value").toDouble();
        if (QObject *obj = settingsPage->findChild<QObject *>("incomingcalls_settings"))
            itsSettings->itsHandleIncomingCalls = obj->property("checked").toBool();
        if (QObject *obj = settingsPage->findChild<QObject *>("sms_settings"))
            itsSettings->itsSendSMS = obj->property("checked").toBool();
        if (QObject *obj = settingsPage->findChild<QObject *>("profile_settings"))
            itsSettings->itsSwitchProfile = obj->property("checked").toBool();
    }
}

void MainWindow::dataChanged()
{
    if (QObject *contact = rootObject()->findChild<QObject *>("contact")) {
        QString text = contact->property("text").toString();
        itsSettings->itsContact.SetNumber(text);
        contact->setProperty("text", itsSettings->itsContact.GetDisplayString());
    }
}

void MainWindow::changeState()
{
    if (QObject *mainPage = rootObject()->findChild<QObject *>("mainPage")) {
        Babyphone::State oldState = itsBabyphone->itsState;
        itsActivationDelayTimer.stop();

        switch (oldState) {
        case Babyphone::STATE_OFF:
            if (itsSettings->itsContact.HasValidNumber()) {
                activateMonitor();
                mainPage->setProperty("state", "WAITING");
            } else {
                if (QObject *banner = rootObject()->findChild<QObject *>("banner")) {
                    banner->setProperty("text",
                        tr("No valid parent's phone number set.\nPlease adjust the application settings."));
                    QMetaObject::invokeMethod(banner, "show");
                }
            }
            break;
        case Babyphone::STATE_WAITING:
        case Babyphone::STATE_ON:
            deactivateMonitor();
            mainPage->setProperty("state", "OFF");
            break;
        default:
            break;
        }
    }
}

void MainWindow::activateMonitor()
{
    itsActivationDelayTimer.start(itsSettings->itsActivationDelay * 1000);
    itsBabyphone->setState(Babyphone::STATE_WAITING);
}

void MainWindow::deactivateMonitor()
{
    itsBabyphone->setState(Babyphone::STATE_OFF);
    if (itsSettings->itsShowStatistics) {
        if (QObject *banner = rootObject()->findChild<QObject *>("banner")) {
            banner->setProperty("text", itsBabyphone->getStatistics());
            QMetaObject::invokeMethod(banner, "show");
        }
    }
}

void MainWindow::newCallStatus(bool finish, bool selfInitiated)
{
    if (finish && selfInitiated) {
        itsBabyphone->setState(Babyphone::STATE_WAITING);
        if (QObject *mainPage = rootObject()->findChild<QObject *>("mainPage"))
            mainPage->setProperty("state", "WAITING");
        itsActivationDelayTimer.start(itsSettings->itsRecallTimer * 1000);
    }
}

void MainWindow::activationTimerExpired()
{
    itsBabyphone->setState(Babyphone::STATE_ON);
    if (QObject *mainPage = rootObject()->findChild<QObject *>("mainPage"))
        mainPage->setProperty("state", "ON");
}

void MainWindow::bringWindowToFront()
{
    activateWindow();
    raise();
}

void MainWindow::newAudioData(int counter, int value)
{
    if (!itsIsScreenOff) {
        if (QObject *volume_graph = rootObject()->findChild<QObject *>("volume_graph"))
            QMetaObject::invokeMethod(volume_graph, "addValue", Q_ARG(int, value));
        if (QObject *duration_graph = rootObject()->findChild<QObject *>("duration_graph"))
            QMetaObject::invokeMethod(duration_graph, "addValue", Q_ARG(int, counter));
    }
}

void MainWindow::showNotificationError()
{
    if (QObject *banner = rootObject()->findChild<QObject *>("banner")) {
        QString errorMsg = itsSettings->itsUserNotifyScript.isEmpty()
            ? tr("Could not establish phone call. Please check network coverage and the phone number settings.")
            : QString(tr("Could not start user script %1.")).arg(itsSettings->itsUserNotifyScript);
        banner->setProperty("text", errorMsg);
        QMetaObject::invokeMethod(banner, "show");
    }
}

void MainWindow::showFirstRunInfo()
{
    if (QObject *banner = rootObject()->findChild<QObject *>("banner")) {
        banner->setProperty("text",
            tr("Babyphone performs audio monitoring even when the device is locked. Battery usage will be higher."));
        banner->setProperty("timerShowTime", 15000);
        QMetaObject::invokeMethod(banner, "show");
    }
}

void MainWindow::showHelp()
{
    QDesktopServices::openUrl(QUrl(BABYPHONE_URL_HELP));
}
