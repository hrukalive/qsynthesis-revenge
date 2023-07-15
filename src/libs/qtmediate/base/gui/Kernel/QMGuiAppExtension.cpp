#include "QMGuiAppExtension.h"

#include <QDir>
#include <QFontDatabase>
#include <QGuiApplication>
#include <QScreen>

#include "QMGuiConsole.h"
#include "QMGuiDecoratorV2.h"
#include "QMSystem.h"

#include "private/QMGuiAppExtension_p.h"
#include "private/QMetaTypeImpl_p.h"

QMCoreConsole *QMGuiInitFactory::createConsole(QObject *parent) {
    return new QMGuiConsole(parent);
}

QMCoreDecoratorV2 *QMGuiInitFactory::createDecorator(QObject *parent) {
    return new QMGuiDecoratorV2(parent);
}

QMGuiAppExtensionPrivate::QMGuiAppExtensionPrivate() {
}

QMGuiAppExtensionPrivate::~QMGuiAppExtensionPrivate() {
}

void QMGuiAppExtensionPrivate::init() {
    // This is necessary for macOS platforms, so that QIcon will return a
    // pixmap with correct devicePixelRatio when using QIcon::pixmap().
    QGuiApplication::setAttribute(Qt::AA_UseHighDpiPixmaps);

    // Must register all meta-types converters in advance
    QMetaTypeImpl::Register();

    for (const auto &path : qAsConst(fontPaths)) {
        QDir directory(path);
        QStringList fontFiles = directory.entryList({"*.ttf", "*.otf"}, QDir::Files);
        foreach (const QString &fontFile, fontFiles) {
            QString fontFilePath = directory.absoluteFilePath(fontFile);
            int fontId = QFontDatabase::addApplicationFont(fontFilePath);
            if (fontId != -1) {
                QStringList fontFamilies = QFontDatabase::applicationFontFamilies(fontId);
                qCDebug(qAppExtLog) << "add font families: " << fontFamilies.join(", ");
            }
        }
    }

    QFont font = QGuiApplication::font();

#ifdef Q_OS_WINDOWS
    // font.setFamily("Microsoft YaHei"); // Consider not using MSYH on non-Chinese Windows platform
#endif

    // Init font
    if (!appFont.isEmpty()) {
        QJsonValue value;
        value = appFont.value("Family");
        if (value.isString()) {
            font.setFamily(value.toString());
        }

        value = appFont.value("Size");
        if (value.isDouble()) {
            double ratio = QGuiApplication::primaryScreen()->logicalDotsPerInch() / QMOs::unitDpi();
            font.setPixelSize(int(value.toDouble() * ratio));
        }

        value = appFont.value("Weight");
        if (value.isDouble()) {
            font.setWeight(value.toInt());
        }
    }

    font.setStyleStrategy(QFont::PreferAntialias);
    qApp->setFont(font);

    // Add icons
    svgs.insert(QMGuiAppExtension::SI_MenuIndicator, QSvgIconEx::fromStringList({
                                                         "svg",
                                                         R"(":/qtmediate.org/svg/check-line.svg", auto)",
                                                     }));
    svgs.insert(QMGuiAppExtension::SI_MenuRightArrow, QSvgIconEx::fromStringList({
                                                          "svg",
                                                          R"(":/qtmediate.org/svg/arrow-right-s-line.svg", auto)",
                                                      }));
    svgs.insert(QMGuiAppExtension::SI_MenuBarExtension, QSvgIconEx::fromStringList({
                                                            "svg",
                                                            R"(":/qtmediate.org/svg/more-line.svg", auto)",
                                                        }));
}

QMCoreInitFactory *QMGuiAppExtensionPrivate::createFactory() {
    return new QMGuiInitFactory();
}

QMGuiAppExtension::QMGuiAppExtension(QObject *parent) : QMGuiAppExtension(*new QMGuiAppExtensionPrivate(), parent) {
}

QMGuiAppExtension::~QMGuiAppExtension() {
}

QSvgIconEx QMGuiAppExtension::svgIcon(SvgIcon icon) const {
    Q_D(const QMGuiAppExtension);
    return d->svgs.value(icon);
}

void QMGuiAppExtension::setSvgIcon(SvgIcon icon, const QSvgIconEx &uri) {
    Q_D(QMGuiAppExtension);
    d->svgs.insert(icon, uri);
}

QMGuiAppExtension::QMGuiAppExtension(QMGuiAppExtensionPrivate &d, QObject *parent) : QMCoreAppExtension(d, parent) {
    d.init();
}