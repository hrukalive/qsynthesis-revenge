#ifndef CHORUSKIT_DSPXTIMELINEENTITY_H
#define CHORUSKIT_DSPXTIMELINEENTITY_H

#include <AceTreeObjectEntity.h>
#include <AceTreeStandardEntity.h>

#include "coreplugin/CoreGlobal.h"

namespace Core {

    class DspxTimelineEntity;
    class DspxTimeSignatureEntity;
    class DspxTimeSignatureListEntity;
    class DspxTempoEntity;
    class DspxTempoListEntity;
    class DspxTimeSignatureEntity;
    class DspxTimelineLabelEntity;
    class DspxTimelineLabelListEntity;

    //===========================================================================
    // Timeline
    class DspxTimelineEntityPrivate;

    class CORE_EXPORT DspxTimelineEntity : public AceTreeStandardEntity {
        Q_OBJECT
        Q_DECLARE_PRIVATE(DspxTimelineEntity)
    public:
        explicit DspxTimelineEntity(QObject *parent = nullptr);
        ~DspxTimelineEntity();

        QString name() const override;

    public:
        DspxTimeSignatureListEntity *timeSignatures() const;
        DspxTempoListEntity *tempos() const;
        DspxTimelineLabelListEntity *labels() const;
    };
    //===========================================================================

    //===========================================================================
    // TimeSignature
    class CORE_EXPORT DspxTimeSignatureEntity : public AceTreeEntityMapping {
        Q_OBJECT
    public:
        explicit DspxTimeSignatureEntity(QObject *parent = nullptr);
        ~DspxTimeSignatureEntity();

        QString name() const override;

    public:
        int position() const;
        void setPosition(int position);

        int numerator() const;
        void setNumerator(int numerator);

        int denominator() const;
        void setDenominator(int denominator);
    };
    //===========================================================================

    //===========================================================================
    // TimeSignature List
    class CORE_EXPORT DspxTimeSignatureListEntity : public AceTreeEntityRecordTable,
                                                    public AceTreeEntityRecordTableHelper<DspxTimeSignatureEntity> {
        Q_OBJECT
    public:
        explicit DspxTimeSignatureListEntity(QObject *parent = nullptr);
        ~DspxTimeSignatureListEntity();

        QString name() const override;

    public:
        void sortRecords(QVector<AceTreeEntity *> &records) const override;
    };
    //===========================================================================

    //===========================================================================
    // Tempo
    class CORE_EXPORT DspxTempoEntity : public AceTreeEntityMapping {
        Q_OBJECT
    public:
        explicit DspxTempoEntity(QObject *parent = nullptr);
        ~DspxTempoEntity();

        QString name() const override;

    public:
        int position() const;
        void setPosition(int position);

        double value() const;
        void setValue(double value);
    };
    //===========================================================================

    //===========================================================================
    // Tempo List
    class CORE_EXPORT DspxTempoListEntity : public AceTreeEntityVector,
                                            public AceTreeEntityVectorHelper<DspxTempoEntity> {
        Q_OBJECT
    public:
        explicit DspxTempoListEntity(QObject *parent = nullptr);
        ~DspxTempoListEntity();

        QString name() const override;

    public:
        void sortRecords(QVector<AceTreeEntity *> &records) const override;
    };
    //===========================================================================

    //===========================================================================
    // TimelineLabel
    class CORE_EXPORT DspxTimelineLabelEntity : public AceTreeEntityMapping {
        Q_OBJECT
    public:
        explicit DspxTimelineLabelEntity(QObject *parent = nullptr);
        ~DspxTimelineLabelEntity();

        QString name() const override;

    public:
        int position() const;
        void setPosition(int position);

        QString text() const;
        void setText(const QString &text);
    };
    //===========================================================================

    //===========================================================================
    // TimelineLabel List
    class CORE_EXPORT DspxTimelineLabelListEntity : public AceTreeEntityVector,
                                                    public AceTreeEntityVectorHelper<DspxTimelineLabelEntity> {
        Q_OBJECT
    public:
        explicit DspxTimelineLabelListEntity(QObject *parent = nullptr);
        ~DspxTimelineLabelListEntity();

        QString name() const override;

    public:
        void sortRecords(QVector<AceTreeEntity *> &records) const override;
    };
    //===========================================================================

}

#endif // CHORUSKIT_DSPXTIMELINEENTITY_H