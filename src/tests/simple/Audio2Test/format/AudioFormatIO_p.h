//
// Created by Crs_1 on 2023/7/12.
//

#ifndef CHORUSKIT_AUDIOFORMATIO_P_H
#define CHORUSKIT_AUDIOFORMATIO_P_H

#include "AudioFormatIO.h"

class AudioFormatIOPrivate {
    Q_DECLARE_PUBLIC(AudioFormatIO)
public:
    AudioFormatIO *q_ptr;
    QIODevice *stream = nullptr;
    QScopedPointer<SndfileHandle> sf;
    AudioFormatIO::OpenMode openMode = QIODevice::NotOpen;

    int64_t sfVioGetFilelen();
    int64_t sfVioSeek(int64_t offset, int whence);
    int64_t sfVioRead(void *ptr, int64_t count);
    int64_t sfVioWrite(const void *ptr, int64_t count);
    int64_t sfVioTell();
};

#endif // CHORUSKIT_AUDIOFORMATIO_P_H
