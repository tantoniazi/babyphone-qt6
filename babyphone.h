#ifndef BABYPHONE_H
#define BABYPHONE_H

#include <QObject>
#include <QTimer>
#include <QDBusVariant>
#include "audiomonitor.h"
#include "callmonitor.h"
#include "usernotifier.h"
#include "profileswitcher.h"
#include "settings.h"

class Babyphone : public QObject
{
    Q_OBJECT
public:
    enum State {
        STATE_OFF,
        STATE_WAITING,
        STATE_ON
    };

    explicit Babyphone(const Settings *settings, QObject *parent = nullptr);
    void setState(State state);
    QString getStatistics() const;

signals:
    void newAudioData(int counter, int value);
    void phoneApplicationFinished();
    void notificationError();
    void newCallStatus(bool finish, bool selfInitiated);

private slots:
    void refreshAudioData(int counter, int value);
    void startAudio();
    void stopAudio();
    void callReceived(QString phoneNumber);
    void callFinished();
    void notifyFinished();
    void phoneAppTimeout();

public:
    State itsState = STATE_OFF;

private:
    const Settings * const itsSettings;
    AudioMonitor *itsAudioMonitor = nullptr;
    CallMonitor *itsCallMonitor = nullptr;
    UserNotifier *itsUserNotifier = nullptr;
    ProfileSwitcher *itsProfileSwitcher = nullptr;
    bool itsNotificationPending = false;
};

#endif // BABYPHONE_H
