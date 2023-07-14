//
// Created by Crs_1 on 2023/7/8.
//

#include "MixerAudioSource.h"
#include "MixerAudioSource_p.h"

#include "buffer/AudioBuffer.h"

MixerAudioSource::MixerAudioSource(): MixerAudioSource(*new MixerAudioSourcePrivate) {
}

MixerAudioSource::MixerAudioSource(MixerAudioSourcePrivate &d): AudioSource(d) {
}

MixerAudioSource::~MixerAudioSource() {
    Q_D(MixerAudioSource);
    MixerAudioSource::close();
    d->deleteOwnedSources();
}

bool MixerAudioSource::open(qint64 bufferSize, double sampleRate) {
    Q_D(MixerAudioSource);
    QMutexLocker locker(&d->mutex);
    if(d->start(bufferSize, sampleRate)) {
        return AudioSource::open(bufferSize, sampleRate);
    } else {
        return false;
    }
}

qint64 MixerAudioSource::read(const AudioSourceReadData &readData) {
    Q_D(MixerAudioSource);
    QList<float> magnitude;
    qint64 readLength = readData.length;
    {
        QMutexLocker locker(&d->mutex);
        auto channelCount = readData.buffer->channelCount();
        AudioBuffer tmpBuf(channelCount, readData.length);
        for(int i = 0; i < channelCount; i++) {
            readData.buffer->clear(i, readData.startPos, readLength);
        }
        for(auto src: sources()) {
            readLength = std::min(readLength, src->read(AudioSourceReadData(&tmpBuf, 0, readLength)));
            for(int i = 0; i < channelCount; i++) {
                readData.buffer->addSampleRange(i, readData.startPos, readLength, tmpBuf, i, 0);
            }
        }
        applyGainAndPan({readData.buffer, readData.startPos, readLength}, d->gain, d->pan);

        for(int i = 0; i < channelCount; i++) {
            magnitude.append(readData.buffer->magnitude(i, readData.startPos, readLength));
        }
    }

    float magL = 0, magR = 0;
    if(magnitude.length() >= 2) {
        magL = magnitude[0];
        magR = magnitude[1];
    } else if(magnitude.length() == 1) {
        magL = magR = magnitude[0];
    }
    emit meterUpdated(magL, magR);
    return readLength;
}

void MixerAudioSource::close() {
    Q_D(MixerAudioSource);
    QMutexLocker locker(&d->mutex);
    d->stop();
    AudioSource::close();
}

bool MixerAudioSource::addSource(AudioSource *src, bool takeOwnership) {
    Q_D(MixerAudioSource);
    QMutexLocker locker(&d->mutex);
    if(src == this) return false;
    if(d->sourceDict.append(src, takeOwnership).second) {
        if(isOpened()) {
            src->open(bufferSize(), sampleRate());
        }
        return true;
    }
    return false;
}
void MixerAudioSource::removeSource(AudioSource *src) {
    Q_D(MixerAudioSource);
    QMutexLocker locker(&d->mutex);
    d->sourceDict.remove(src);
}
void MixerAudioSource::removeAllSource() {
    Q_D(MixerAudioSource);
    QMutexLocker locker(&d->mutex);
    d->sourceDict.clear();
}
QList<AudioSource *> MixerAudioSource::sources() const {
    Q_D(const MixerAudioSource);
    return d->sourceDict.keys();
}

void IMixer::deleteOwnedSources() const {
    for(auto src: sourceDict.keys()) {
        if(sourceDict.value(src)) {
            delete src;
        }
    }
}
bool IMixer::start(qint64 bufferSize, double sampleRate) const {
    auto sourceList = sourceDict.keys();
    if(std::all_of(sourceList.constBegin(), sourceList.constEnd(), [=](AudioSource *src){
            return src->open(bufferSize, sampleRate);
        })) {
        return true;
    } else {
        return false;
    }
}
void IMixer::stop() const {
    auto sourceList = sourceDict.keys();
    std::for_each(sourceList.constBegin(), sourceList.constEnd(), [=](AudioSource *src){ src->close();
    });
}

void MixerAudioSource::setGain(float gain) {
    Q_D(MixerAudioSource);
    QMutexLocker locker(&d->mutex);
    d->gain = gain;
}
float MixerAudioSource::gain() const {
    Q_D(const MixerAudioSource);
    return d->gain;
}
void MixerAudioSource::setPan(float pan) {
    Q_D(MixerAudioSource);
    QMutexLocker locker(&d->mutex);
    d->pan = pan;
}
float MixerAudioSource::pan() const {
    Q_D(const MixerAudioSource);
    return d->pan;
}
