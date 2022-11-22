#include "CDockPanel.h"

CDockPanel::CDockPanel(QWidget *parent) : QSplitter(parent) {
    init();
}

CDockPanel::CDockPanel(Qt::Orientation orient, QWidget *parent)
    : QSplitter(orient, parent) {
    init();
}

CDockPanel::~CDockPanel() {
}

void CDockPanel::init() {
    setChildrenCollapsible(false);

    m_firstWidget = new QStackedWidget();
    m_secondWidget = new QStackedWidget();

    QSplitter::addWidget(m_firstWidget);
    QSplitter::addWidget(m_secondWidget);

    m_firstWidget->hide();
    m_secondWidget->hide();
    updateVisible();
}

int CDockPanel::addWidget(Qs::Priority num, QWidget *w, bool visible) {
    return insertWidget(num, (num == Qs::Primary) ? m_firstWidget->count() : m_secondWidget->count(),
                        w, visible);
}

int CDockPanel::insertWidget(Qs::Priority num, int index, QWidget *w, bool visible) {
    QStackedWidget *container = (num == Qs::Primary) ? m_firstWidget : m_secondWidget;
    int res = container->insertWidget(index, w);

    if (visible) {
        container->show();
        container->setCurrentWidget(w);
        if (!isVisible()) {
            show();
        }
    } /* else {
         container->hide();
         updateVisible();
     }*/
    return res;
}

void CDockPanel::removeWidget(Qs::Priority num, QWidget *w) {
    QStackedWidget *container = (num == Qs::Primary) ? m_firstWidget : m_secondWidget;
    bool isCurrent = container->currentWidget() == w;
    container->removeWidget(w);

    if (isCurrent && container->isVisible()) {
        container->hide();
        updateVisible();
    }
}

QWidget *CDockPanel::currentWidget(Qs::Priority num) const {
    QStackedWidget *container = (num == Qs::Primary) ? m_firstWidget : m_secondWidget;
    return container->currentWidget();
}

int CDockPanel::currentIndex(Qs::Priority num) const {
    QStackedWidget *container = (num == Qs::Primary) ? m_firstWidget : m_secondWidget;
    return container->currentIndex();
}

int CDockPanel::indexOf(Qs::Priority num, QWidget *w) const {
    QStackedWidget *container = (num == Qs::Primary) ? m_firstWidget : m_secondWidget;
    return container->indexOf(w);
}

QWidget *CDockPanel::widget(Qs::Priority num, int index) const {
    QStackedWidget *container = (num == Qs::Primary) ? m_firstWidget : m_secondWidget;
    return container->widget(index);
}

int CDockPanel::count(Qs::Priority num) const {
    QStackedWidget *container = (num == Qs::Primary) ? m_firstWidget : m_secondWidget;
    return container->count();
}

void CDockPanel::setCurrentIndex(Qs::Priority num, int index) {
    QStackedWidget *container = (num == Qs::Primary) ? m_firstWidget : m_secondWidget;
    return container->setCurrentIndex(index);
}

void CDockPanel::setCurrentWidget(Qs::Priority num, QWidget *w) {
    QStackedWidget *container = (num == Qs::Primary) ? m_firstWidget : m_secondWidget;
    return container->setCurrentWidget(w);
}

void CDockPanel::setContainerVisible(Qs::Priority num, bool visible) {
    QStackedWidget *container = (num == Qs::Primary) ? m_firstWidget : m_secondWidget;
    container->setVisible(visible);
    if (visible) {
        show();
    } else {
        updateVisible();
    }
}

void CDockPanel::updateVisible() {
    if (!m_firstWidget->isVisible() && !m_secondWidget->isVisible()) {
        hide();
    }
}
