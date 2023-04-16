#ifndef DOCUMENTSPEC_H
#define DOCUMENTSPEC_H

#include <QObject>

#include "CkAppCoreGlobal.h"

namespace Core {

    class DocumentSpecPrivate;

    class CKAPPCORE_API DocumentSpec : public QObject {
        Q_OBJECT
        Q_DECLARE_PRIVATE(DocumentSpec)
    public:
        explicit DocumentSpec(const QString &id, QObject *parent = nullptr);
        ~DocumentSpec();

    public:
        QString id() const;

    public:
        virtual QStringList supportedExtensions() const = 0;
        virtual QString filter() const = 0;
        virtual QString saveFilter() const;
        virtual bool open(const QString &filename) = 0;

    protected:
        DocumentSpec(DocumentSpecPrivate &d, const QString &id, QObject *parent = nullptr);

        QScopedPointer<DocumentSpecPrivate> d_ptr;
    };

}

#endif // DOCUMENTSPEC_H