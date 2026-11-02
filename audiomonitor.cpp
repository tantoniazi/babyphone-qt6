#include "audiomonitor.h"

#include <QDebug>
#include <cmath>
#include <ctime>

AudioMonitor::AudioMonitor(const Settings *settings, QObject *parent)
    : QIODevice(parent), itsSettings(settings)
{
    open(QIODevice::WriteOnly);
    itsActive = false;
    itsCounter = 0;
    std::srand(std::time(nullptr));
}

AudioMonitor::~AudioMonitor()
{
    if (itsActive)
        stop();
    close();
}

bool AudioMonitor::start()
{
    if (!itsActive) {
        // Modo simulação: gera níveis de áudio simulados via timer
        simTimer = new QTimer(this);
        connect(simTimer, &QTimer::timeout, this, [this]() {
            // Simula volume aleatório (0-200) e contador
            simulatedVolume = std::rand() % 200;
            if (simulatedVolume > itsSettings->THRESHOLD_VALUE) {
                simulatedCounter += itsSettings->itsDurationInfluence;
                if (simulatedCounter / COUNTER_SCALE_FACTOR > itsSettings->VOLUME_COUNTER_MAX) {
                    simulatedCounter = itsSettings->VOLUME_COUNTER_MAX * COUNTER_SCALE_FACTOR;
                }
            } else {
                simulatedCounter -= itsSettings->VOLUME_COUNTER_DEC;
                if (simulatedCounter < 0)
                    simulatedCounter = 0;
            }
            emit update(simulatedCounter / COUNTER_SCALE_FACTOR, simulatedVolume);
        });
        simTimer->start(itsSettings->AUDIO_SAMPLE_INTERVAL);
        itsActive = true;
        qDebug() << "AudioMonitor started (simulation mode)";
    }
    return true;
}

void AudioMonitor::stop()
{
    itsActive = false;
    if (simTimer) {
        simTimer->stop();
        simTimer->deleteLater();
        simTimer = nullptr;
    }
    qDebug() << "AudioMonitor stopped";
}

qint64 AudioMonitor::readData(char *data, qint64 maxlen)
{
    Q_UNUSED(data);
    Q_UNUSED(maxlen);
    return 0;
}

qint64 AudioMonitor::writeData(const char *data, qint64 len)
{
    Q_UNUSED(data);
    Q_UNUSED(len);
    return 0;
}
