#ifndef AUDIOMONITOR_H
#define AUDIOMONITOR_H

#include <QObject>
#include <QIODevice>
#include <QTimer>
#include "settings.h"

class AudioMonitor : public QIODevice
{
    Q_OBJECT
public:
    AudioMonitor(const Settings *settings, QObject *parent = nullptr);
    ~AudioMonitor() override;

    bool start();
    void stop();

private:
    qint64 readData(char *data, qint64 maxlen) override;
    qint64 writeData(const char *data, qint64 len) override;

signals:
    void update(int counter, int value);

public:
    int itsCounter = 0;
    bool itsActive = false;

private:
    const static int COUNTER_SCALE_FACTOR = 5;
    const Settings * const itsSettings;
    QTimer *simTimer = nullptr;
    int simulatedVolume = 0;
    int simulatedCounter = 0;
};

#endif // AUDIOMONITOR_H
