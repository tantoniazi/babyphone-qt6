#ifndef BABYPHONEDEFINES_H
#define BABYPHONEDEFINES_H

#include <QString>

#define BABYPHONE_VERSION "2.0"
#define BABYPHONE_URL_HELP "http://babyphone.garage.maemo.org/index.html#sec_settings"

// Settings keys and defaults
#define COMPANY "morawek.at"
#define PRODUCT "babyphone"
#define CONTACT_PHONENUMBER_KEY "contact/phoneNumber"
#define CONTACT_PHONENUMBER_DEFAULT ""
#define CONTACT_NAME_KEY "contact/name"
#define CONTACT_NAME_DEFAULT ""
#define USER_NOTIFY_SCRIPT_KEY "application/notifyScript"
#define USER_NOTIFY_SCRIPT_DEFAULT ""
#define AUDIO_AMPLIFY_KEY "audio/volume"
#define AUDIO_AMPLIFY_DEFAULT 16
#define AUDIO_TIMER_KEY "audio/timer"
#define AUDIO_TIMER_DEFAULT 10
#define CALL_SETUP_TIMER_KEY "call/setupTimer"
#define CALL_SETUP_TIMER_DEFAULT 30
#define ACTIVATION_DELAY_KEY "application/activationDelay"
#define ACTIVATION_DELAY_DEFAULT 0
#define RECALL_TIMER_KEY "call/recallTimer"
#define RECALL_TIMER_DEFAULT 180
#define SWITCH_PROFILE_KEY "application/switchProfile"
#define SWITCH_PROFILE_DEFAULT true
#define FIRST_RUN_KEY "application/firstRun"
#define SEND_SMS_KEY "application/sendSMS"
#define SEND_SMS_DEFAULT false
#define SHOW_STATISTICS_KEY "application/showStatistics"
#define SHOW_STATISTICS_DEFAULT true
#define REJECT_INCOMING_CALLS_KEY "call/rejectIncoming"
#define REJECT_INCOMING_CALLS_DEFAULT true
#define DISABLE_GRAPHS_KEY "view/disableGraphsWhileLocked"
#define DISABLE_GRAPHS_DEFAULT true
#define DISABLE_AUTOROTATE_KEY "view/disableAutoRotate"
#define DISABLE_AUTOROTATE_DEFAULT false

// Constant settings (ms or values)
#define CALL_HOLD_TIMER_MS 300000
#define THRESHOLD_VALUE_DEFAULT 100
#define VOLUME_COUNTER_MAX_DEFAULT 120
#define VOLUME_COUNTER_DEC_DEFAULT 3
#define NOTIFY_SCRIPT_START_TIMEOUT_MS 2000
#define MSG_BOX_TIMEOUT_MS 10000
#define REFOCUS_TIMER_MS 2000
#define AUDIO_SAMPLE_INTERVAL_MS 800
#define AUDIO_SAMPLE_SUBINTERVAL_DEFAULT 16
#define AUDIO_RETRY_TIMER_MS 5000

#endif // BABYPHONEDEFINES_H
