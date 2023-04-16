#ifndef DOCUMENTSYSTEM_H
#define DOCUMENTSYSTEM_H

#include "DocumentSpec.h"
#include "DocumentWatcher.h"

namespace Core {

    class DocumentSystemPrivate;

    class CKAPPCORE_API DocumentSystem : public DocumentWatcher {
        Q_OBJECT
        Q_DECLARE_PRIVATE(DocumentSystem)
    public:
        explicit DocumentSystem(QObject *parent = nullptr);
        ~DocumentSystem();

    public:
        bool addDocType(DocumentSpec *doc);
        bool removeDocType(DocumentSpec *doc);
        bool removeDocType(const QString &id);
        DocumentSpec *docType(const QString &id) const;
        QList<DocumentSpec *> docTypes() const;
        QStringList docTypeIds() const;

        QList<DocumentSpec *> supportedDocTypes(const QString &suffix) const;

        // recent files
        void addRecentFile(const QString &fileName);
        void clearRecentFiles();
        QStringList recentFiles() const;

        // recent dirs
        void addRecentDir(const QString &fileName);
        void clearRecentDirs();
        QStringList recentDirs() const;

        bool openFileBrowse(DocumentSpec *spec, const QString &path = {}, QWidget *parent = nullptr) const;

    public:
        QString getOpenFileName(QWidget *parent, const QString &title, const QString &filters, const QString &path = {},
                                QString *selectedFilter = nullptr) const;

        QStringList getOpenFileNames(QWidget *parent, const QString &title, const QString &filters,
                                     const QString &path = {}, QString *selectedFilter = nullptr) const;

        QString getExistingDirectory(QWidget *parent, const QString &title, const QString &path = {}) const;

        QString getSaveFileName(QWidget *parent, const QString &title, const QString &path = {},
                                const QString &filter = QString(), QString *selectedFilter = nullptr) const;

    protected:
        QString getSaveAsFileName(const IDocument *document, QWidget *parent) override;

    signals:
        void recentFilesChanged();
        void recentDirsChanged();

    protected:
        DocumentSystem(DocumentSystemPrivate &d, QObject *parent = nullptr);
    };

}

#endif // DOCUMENTSYSTEM_H