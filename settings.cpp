#include "settings.h"

Settings::Settings(QObject *parent) :
    QSettings(COMPANY, PRODUCT, parent),
    VERSION(BABYPHONE_VERSION),
    CALL_HOLD_TIMER(CALL_HOLD_TIMER_MS),
    THRESHOLD_VALUE(THRESHOLD_VALUE_DEFAULT),
    VOLUME_COUNTER_MAX(VOLUME_COUNTER_MAX_DEFAULT),
    VOLUME_COUNTER_DEC(VOLUME_COUNTER_DEC_DEFAULT),
    NOTIFY_SCRIPT_START_TIMEOUT(NOTIFY_SCRIPT_START_TIMEOUT_MS),
    MSG_BOX_TIMEOUT(MSG_BOX_TIMEOUT_MS),
    REFOCUS_TIMER(REFOCUS_TIMER_MS),
    AUDIO_SAMPLE_INTERVAL(AUDIO_SAMPLE_INTERVAL_MS),
    AUDIO_SAMPLE_SUBINTERVAL(AUDIO_SAMPLE_SUBINTERVAL),
    AUDIO_RETRY_TIMER(AUDIO_RETRY_TIMER_MS)
{
    itsAudioAmplify = value(AUDIO_AMPLIFY_KEY, AUDIO_AMPLIFY_DEFAULT).toInt();
    itsDurationInfluence = value(AUDIO_TIMER_KEY, AUDIO_TIMER_DEFAULT).toInt();
    itsContact.itsPhoneNumber = value(CONTACT_PHONENUMBER_KEY, CONTACT_PHONENUMBER_DEFAULT).toString();
    itsContact.itsName = value(CONTACT_NAME_KEY, CONTACT_NAME_DEFAULT).toString();
    itsUserNotifyScript = value(USER_NOTIFY_SCRIPT_KEY, USER_NOTIFY_SCRIPT_DEFAULT).toString();
    itsCallSetupTimer = value(CALL_SETUP_TIMER_KEY, CALL_SETUP_TIMER_DEFAULT).toInt();
    itsActivationDelay = value(ACTIVATION_DELAY_KEY, ACTIVATION_DELAY_DEFAULT).toInt();
    itsRecallTimer = value(RECALL_TIMER_KEY, RECALL_TIMER_DEFAULT).toInt();
    itsSwitchProfile = value(SWITCH_PROFILE_KEY, SWITCH_PROFILE_DEFAULT).toBool();
    itsSendSMS = value(SEND_SMS_KEY, SEND_SMS_DEFAULT).toBool();
    itsShowStatistics = value(SHOW_STATISTICS_KEY, SHOW_STATISTICS_DEFAULT).toBool();
    itsHandleIncomingCalls = value(REJECT_INCOMING_CALLS_KEY, REJECT_INCOMING_CALLS_DEFAULT).toBool();
    itsDisableGraphs = value(DISABLE_GRAPHS_KEY, DISABLE_GRAPHS_DEFAULT).toBool();
    itsDisableAutoRotate = value(DISABLE_AUTOROTATE_KEY, DISABLE_AUTOROTATE_DEFAULT).toBool();
    itsFirstRun = value(FIRST_RUN_KEY, true).toBool();
}

void Settings::Save()
{
    setValue(FIRST_RUN_KEY, false);
    setValue(AUDIO_AMPLIFY_KEY, itsAudioAmplify);
    setValue(AUDIO_TIMER_KEY, itsDurationInfluence);
    setValue(CONTACT_PHONENUMBER_KEY, itsContact.itsPhoneNumber);
    setValue(CONTACT_NAME_KEY, itsContact.itsName);
    setValue(USER_NOTIFY_SCRIPT_KEY, itsUserNotifyScript);
    setValue(CALL_SETUP_TIMER_KEY, itsCallSetupTimer);
    setValue(ACTIVATION_DELAY_KEY, itsActivationDelay);
    setValue(RECALL_TIMER_KEY, itsRecallTimer);
    setValue(SWITCH_PROFILE_KEY, itsSwitchProfile);
    setValue(SEND_SMS_KEY, itsSendSMS);
    setValue(SHOW_STATISTICS_KEY, itsShowStatistics);
    setValue(REJECT_INCOMING_CALLS_KEY, itsHandleIncomingCalls);
    setValue(DISABLE_GRAPHS_KEY, itsDisableGraphs);
    setValue(DISABLE_AUTOROTATE_KEY, itsDisableAutoRotate);
}
