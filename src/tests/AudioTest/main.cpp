#include "AudioTrack.h"
#include "Pcm32BitFloatAudioSource.h"
#include <QApplication>
#include <QDebug>

extern "C" {
#include "libavcodec/avcodec.h"
#include "libavformat/avformat.h"
#include "libavformat/avio.h"
}

int main(int argc, char *argv[]) {
    QApplication a(argc, argv);

//    if (argc < 2) {
//        qDebug().noquote() << QString("%1: <file>").arg(qAppName());
//        return 0;
//    }

//    QString fileName = QApplication::arguments().at(1);

    Pcm32BitFloatAudioSource src1("D:\\Downloads\\test_source1.pcm", 48000, 2);
    Pcm32BitFloatAudioSource src2("D:\\Downloads\\test_source2.pcm", 48000, 2);
    AudioTrack track(2, 48000);
    assert(track.addSource(&src1));
    track.addSource(&src2);
    QFile f1("D:\\Downloads\\test_output_c1.pcm");
    QFile f2("D:\\Downloads\\test_output_c2.pcm");
    f1.open(QIODevice::WriteOnly);
    f2.open(QIODevice::WriteOnly);
    AudioBuffer buf(2, 1024);
    for(int i = 0; i < 1048576 / 1024; i++) {
        buf.clear();
        track.read(&buf, 1024, IAudioSource::Immediate);
        f1.write((char*)buf.buffer(0), 1024 * sizeof(float));
        f2.write((char*)buf.buffer(1), 1024 * sizeof(float));
    }
    return 0;
}