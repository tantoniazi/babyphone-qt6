#ifndef CALLMONITOR_H
#define CALLMONITOR_H

#include <QObject>
#include <QTimer>
#include "settings.h"

class QDBusMessage;

class CallMonitor : public QObject
{
    Q_OBJECT
public:
    explicit CallMonitor(const Settings *settings, QObject *parent = nullptr);
    bool dropCall() const;
    void takeCall();

private:
    bool takeCallNow();

signals:
    void callReceived(const QString phoneNumber);
    void callFinished();
    void callStatusChanged(bool newStatus);
    void myCallFinished();

private slots:
    void receiveCall(const QDBusMessage &);
    void callStatusUpdate(const QDBusMessage &);
    void callEstablished(const QDBusMessage &);
    void callTimer();

public:
    bool itsCallPending = false;
    bool itsTakenCallPending = false;

private:
    const Settings* const itsSettings;
    QTimer *itsCallTimer = nullptr;
    bool itsTakeNextCall = false;
};

#endif // CALLMONITOR_H
