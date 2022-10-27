#include "HomeWindow.h"
#include "private/HomeWindow_p.h"

#include "QPixelSize.h"
#include "QSvgUri.h"

#include "Kernel/LvApplication.h"
#include "Managers/WindowManager.h"

#include "Managers/PluginManager.h"

#include <QDebug>

#include "Serialization/QLVProject.h"

#define DECODE_STYLE(VAR, VARIANT, TYPE)                                                           \
    {                                                                                              \
        QVariant var = VARIANT;                                                                    \
        if (var.convert(qMetaTypeId<TYPE>())) {                                                    \
            VAR = var.value<TYPE>();                                                               \
        }                                                                                          \
    }

#define DECODE_STYLE_SETTER(VAR, VARIANT, TYPE, SETTER)                                            \
    {                                                                                              \
        QVariant var = VARIANT;                                                                    \
        if (var.convert(qMetaTypeId<TYPE>())) {                                                    \
            VAR.SETTER(var.value<TYPE>());                                                         \
        }                                                                                          \
    }

HomeWindow::HomeWindow(QWidget *parent) : HomeWindow(*new HomeWindowPrivate(), parent) {
    LVModel::ProjectModel proj;

    qDebug() << proj.load("test.lvproj");
}

HomeWindow::~HomeWindow() {
}

void HomeWindow::reloadStrings() {
    Q_D(HomeWindow);
    d->reloadStrings_helper();
}

QTypeList HomeWindow::templateStyleData() const {
    Q_D(const HomeWindow);
    return {
        QVariant::fromValue(d->emptyItemConfig.icon),
        d->emptyItemConfig.iconSize.width(),
        d->emptyItemConfig.iconSize.height(),
        QVariant::fromValue(d->opencpopItemConfig.icon),
        d->opencpopItemConfig.iconSize.width(),
        d->opencpopItemConfig.iconSize.height(),
        QVariant::fromValue(d->diffItemConfig.icon),
        d->diffItemConfig.iconSize.width(),
        d->diffItemConfig.iconSize.height(),
        QVariant::fromValue(d->openvpiItemConfig.icon),
        d->openvpiItemConfig.iconSize.width(),
        d->openvpiItemConfig.iconSize.height(),
    };
}

void HomeWindow::setTemplateStyleData(const QTypeList &list) {
    Q_D(HomeWindow);
    if (list.size() >= 12) {
        int i = 0;
        DECODE_STYLE(d->emptyItemConfig.icon, list.at(i++), QSvgUri);
        DECODE_STYLE_SETTER(d->emptyItemConfig.iconSize, list.at(i++), QPixelSize, setWidth);
        DECODE_STYLE_SETTER(d->emptyItemConfig.iconSize, list.at(i++), QPixelSize, setHeight);

        DECODE_STYLE(d->opencpopItemConfig.icon, list.at(i++), QSvgUri);
        DECODE_STYLE_SETTER(d->opencpopItemConfig.iconSize, list.at(i++), QPixelSize, setWidth);
        DECODE_STYLE_SETTER(d->opencpopItemConfig.iconSize, list.at(i++), QPixelSize, setHeight);

        DECODE_STYLE(d->diffItemConfig.icon, list.at(i++), QSvgUri);
        DECODE_STYLE_SETTER(d->diffItemConfig.iconSize, list.at(i++), QPixelSize, setWidth);
        DECODE_STYLE_SETTER(d->diffItemConfig.iconSize, list.at(i++), QPixelSize, setHeight);

        DECODE_STYLE(d->openvpiItemConfig.icon, list.at(i++), QSvgUri);
        DECODE_STYLE_SETTER(d->openvpiItemConfig.iconSize, list.at(i++), QPixelSize, setWidth);
        DECODE_STYLE_SETTER(d->openvpiItemConfig.iconSize, list.at(i++), QPixelSize, setHeight);

        d->reloadTemplates();
        emit styleDataChanged();
    }
}

HomeWindow::HomeWindow(HomeWindowPrivate &d, QWidget *parent) : PlainWindow(d, parent) {
    d.init();

    Q_TR_NOTIFY(HomeWindow)
}

void HomeWindow::_q_searchBoxChanged(const QString &text) {
    qDebug() << text;
}
