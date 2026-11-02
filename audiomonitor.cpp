#include "audiomonitor.h"

#include <cmath>
#include <QDebug>
#include <QAudioDeviceInfo>

AudioMonitor::AudioMonitor(const Settings *settings, QObject *parent)
    : QIODevice(parent), itsSettings(settings)
{
    open(QIODevice::WriteOnly);

    QAudioFormat audioFormat;
    audioFormat.setFrequency(8000);
    audioFormat.setChannels(1);
    audioFormat.setSampleSize(16);
    audioFormat.setSampleType(QAudioFormat::SignedInt);
    audioFormat.setByteOrder(QAudioFormat::LittleEndian);
    audioFormat.setCodec("audio/pcm");

    QAudioDeviceInfo info(QAudioDeviceInfo::defaultInputDevice());
    if (!info.isFormatSupported(audioFormat)) {
        audioFormat = info.nearestFormat(audioFormat);
        qWarning() << "Could not get desired audio format";
    }
    if (audioFormat.sampleSize() != 16) {
        qCritical() << "Audio device doesn't support needed format";
        return;
    }

    itsDevice = new QAudioInput(audioFormat, this);
    itsDevice->setNotifyInterval(itsSettings->AUDIO_SAMPLE_INTERVAL);
    itsActive = false;
    itsCounter = 0;
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
        itsDevice->start(this);
        if (itsDevice->error() == QAudio::NoError) {
            itsActive = true;
        } else {
            return false;
        }
    }
    return true;
}

void AudioMonitor::stop()
{
    itsActive = false;
    itsDevice->stop();
}

qint64 AudioMonitor::readData(char *data, qint64 maxlen)
{
    Q_UNUSED(data);
    Q_UNUSED(maxlen);
    return 0;
}

qint64 AudioMonitor::writeData(const char *data, qint64 len)
{
    quint32 curEnergy = 0;
    qint16 max = 0;
    qint16 samples = len / 2;
    const qint16 *buffer = reinterpret_cast<const qint16 *>(data);

    for (int i = 0; i < samples; ++i) {
        if (*buffer > max)
            max = *buffer;
        if ((i % itsSettings->AUDIO_SAMPLE_SUBINTERVAL) == 0) {
            curEnergy += max;
            max = 0;
        }
        buffer++;
    }

    int volume = itsSettings->itsAudioAmplify *
                 std::log(curEnergy * itsSettings->AUDIO_SAMPLE_SUBINTERVAL / (float)samples);
    if (volume < 0)
        volume = 0;

    if (volume > itsSettings->THRESHOLD_VALUE) {
        itsCounter += itsSettings->itsDurationInfluence;
        if (itsCounter / COUNTER_SCALE_FACTOR > itsSettings->VOLUME_COUNTER_MAX) {
            itsCounter = itsSettings->VOLUME_COUNTER_MAX * COUNTER_SCALE_FACTOR;
        }
    } else {
        itsCounter -= itsSettings->VOLUME_COUNTER_DEC;
        if (itsCounter < 0)
            itsCounter = 0;
    }

    emit update(itsCounter / COUNTER_SCALE_FACTOR, volume);
    return len;
}
