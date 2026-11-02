#ifndef USERNOTIFIER_H
#define USERNOTIFIER_H

#include <QObject>
#include "settings.h"
#include "callmonitor.h"

class UserNotifier : public QObject
{
    Q_OBJECT
public:
    UserNotifier(const Settings *settings, CallMonitor *callMonitor, QObject *parent = nullptr);
    bool Notify();
    void notifySMS(const QString &phoneNumber);

signals:
    void notifyFinished();

public:
    int itsCallCounterInvoke = 0;
    int itsCallCounterTaken = 0;
    int itsCallCounterTimeout = 0;

private:
    const Settings * const itsSettings;
    CallMonitor * const itsCallMonitor;
};

#endif // USERNOTIFIER_H
