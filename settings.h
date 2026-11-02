#ifndef SETTINGS_H
#define SETTINGS_H

#include <QSettings>
#include <QObject>
#include "contact.h"
#include "babyphonedefines.h"

class Settings : public QSettings
{
    Q_OBJECT
public:
    explicit Settings(QObject *parent = nullptr);
    void Save();

public:
    Contact itsContact;
    QString itsUserNotifyScript;
    int itsAudioAmplify;
    int itsDurationInfluence;
    int itsCallSetupTimer;
    bool itsSwitchProfile;
    bool itsHandleIncomingCalls;
    bool itsSendSMS;
    bool itsShowStatistics;
    int itsActivationDelay;
    int itsRecallTimer;
    bool itsDisableGraphs;
    bool itsDisableAutoRotate;
    bool itsFirstRun;

    const QString VERSION;
    const int CALL_HOLD_TIMER;
    const int THRESHOLD_VALUE;
    const int VOLUME_COUNTER_MAX;
    const int VOLUME_COUNTER_DEC;
    const int NOTIFY_SCRIPT_START_TIMEOUT;
    const int MSG_BOX_TIMEOUT;
    const int REFOCUS_TIMER;
    const int AUDIO_SAMPLE_INTERVAL;
    const int AUDIO_SAMPLE_SUBINTERVAL;
    const int AUDIO_RETRY_TIMER;
};

#endif // SETTINGS_H
