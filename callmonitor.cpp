#include "callmonitor.h"

#include <QtDBus>

#define CSD_CALL_STATUS_COMING 2
#define CSD_CALL_STATUS_MT_ALERTING 5
#define CSD_CALL_STATUS_TERMINATED 15

CallMonitor::CallMonitor(const Settings *settings, QObject *parent)
    : QObject(parent), itsSettings(settings)
{
    itsCallPending = false;
    itsTakenCallPending = false;
    itsTakeNextCall = false;

    itsCallTimer = new QTimer(this);
    itsCallTimer->setSingleShot(true);
    connect(itsCallTimer, &QTimer::timeout, this, &CallMonitor::callTimer);

    bool result = QDBusConnection::systemBus().connect("com.nokia.csd.Call",
        "/com/nokia/csd/call", "com.nokia.csd.Call", "Coming",
        this, SLOT(receiveCall(const QDBusMessage &)));
    if (!result)
        qWarning() << "Cannot connect to incoming calls";

    result = QDBusConnection::systemBus().connect("com.nokia.csd.Call",
        "/com/nokia/csd/call/1", "com.nokia.csd.Call.Instance",
        "CallStatus", this, SLOT(callStatusUpdate(const QDBusMessage &)));
    if (!result)
        qWarning() << "Cannot connect to call status";

    result = QDBusConnection::systemBus().connect("com.nokia.csd.Call",
        "/com/nokia/csd/call/1", "com.nokia.csd.Call.Instance",
        "AudioConnect", this, SLOT(callEstablished(const QDBusMessage &)));
    if (!result)
        qWarning() << "Cannot connect to audio connect";
}

void CallMonitor::receiveCall(const QDBusMessage &msg)
{
    QList<QVariant> lst = msg.arguments();
    QString caller = lst[1].toString();
    qDebug() << "Receive call from" << caller;
    itsTakeNextCall = false;
    emit callReceived(caller);
}

void CallMonitor::callStatusUpdate(const QDBusMessage &msg)
{
    int callStatus = msg.arguments()[0].toInt();
    if (itsTakeNextCall && callStatus >= CSD_CALL_STATUS_MT_ALERTING) {
        itsTakeNextCall = false;
        takeCallNow();
    }
    if (callStatus == CSD_CALL_STATUS_TERMINATED) {
        qDebug() << "Call finished.";
        emit callFinished();
    }
}

void CallMonitor::callEstablished(const QDBusMessage &msg)
{
    bool flag0 = msg.arguments()[0].toBool();
    bool flag1 = msg.arguments()[1].toBool();
    if (flag0 && flag1) {
        itsCallPending = true;
        emit callStatusChanged(true);
    } else if (!flag0 && !flag1) {
        itsCallTimer->stop();
        if (itsTakenCallPending) {
            emit myCallFinished();
            itsTakenCallPending = false;
        }
        itsCallPending = false;
        emit callStatusChanged(false);
    }
}

bool CallMonitor::dropCall() const
{
    QDBusMessage msg = QDBusMessage::createMethodCall(
        "com.nokia.csd.Call", "/com/nokia/csd/call",
        "com.nokia.csd.Call", "Release");
    QDBusMessage reply = QDBusConnection::systemBus().call(msg);
    if (reply.type() == QDBusMessage::ErrorMessage) {
        qWarning() << "Call handling failed";
        return false;
    }
    qDebug() << "Call dropped";
    return true;
}

void CallMonitor::takeCall()
{
    itsTakeNextCall = true;
}

bool CallMonitor::takeCallNow()
{
    QDBusMessage msg = QDBusMessage::createMethodCall(
        "com.nokia.csd.Call", "/com/nokia/csd/call/1",
        "com.nokia.csd.Call.Instance", "Answer");
    QDBusMessage reply = QDBusConnection::systemBus().call(msg);
    if (reply.type() == QDBusMessage::ErrorMessage) {
        qWarning() << "Call handling failed";
        emit myCallFinished();
        return false;
    }
    qDebug() << "Call taken";
    itsTakenCallPending = true;
    itsCallTimer->start(itsSettings->CALL_HOLD_TIMER);
    return true;
}

void CallMonitor::callTimer()
{
    dropCall();
    if (itsTakenCallPending) {
        emit myCallFinished();
        itsTakenCallPending = false;
    }
}
