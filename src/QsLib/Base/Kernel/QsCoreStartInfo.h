#ifndef QSCORESTARTINFO_H
#define QSCORESTARTINFO_H

#include <QCommandLineParser>
#include <QString>

#include "QsGlobal.h"
#include "QMDisposable.h"

#ifndef qIStup
#    define qIStup QsCoreStartInfo::instance()
#endif

class QsCoreConsole;
class QsCoreDecorator;
class QsCoreConfig;
class QsCoreStartInfoPrivate;

class QSBASE_API QsCoreStartInfo : public QMDisposable {
    Q_OBJECT
    Q_DECLARE_PRIVATE(QsCoreStartInfo)
    Q_SINGLETON(QsCoreStartInfo)
public:
    explicit QsCoreStartInfo(QObject *parent = nullptr);
    ~QsCoreStartInfo();

protected:
    void loadImpl() override;
    void saveImpl() override;

public:
    bool isAboutToQuit() const;

    /* Properties can be append in each app's constructor */
    QCommandLineParser parser;

    /* Properties setup in main functions */
    QString appDescription;

    bool allowRootUser;  // Default: false

    bool allowSecondary; // Default: false

    virtual QString mainTitle() const;

    virtual QString windowTitle() const;

    virtual QString errorTitle() const;

    /* Factory */
protected:
    virtual QsCoreConsole *createConsole(QObject *parent = nullptr);

    virtual QsCoreDecorator *createDecorator(QObject *parent = nullptr);

    virtual QsCoreConfig *creatDistConfig();

protected:
    QsCoreStartInfo(QsCoreStartInfoPrivate &d, QObject *parent = nullptr);

    QScopedPointer<QsCoreStartInfoPrivate> d_ptr;

    virtual void newStartedInstance();
    virtual void receiveMessage(quint32 instanceId, const QByteArray &message);
    virtual void clean();

private:
    void _q_instanceStarted();
    void _q_messageReceived(quint32 instanceId, QByteArray message);
    void _q_aboutToQuit();
};

#endif // QSCORESTARTINFO_H
