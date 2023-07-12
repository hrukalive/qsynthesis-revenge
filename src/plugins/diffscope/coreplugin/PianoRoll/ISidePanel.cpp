#include "ISidePanel.h"
#include "ISidePanel_p.h"

#include <QApplication>
#include <QContextMenuEvent>
#include <QStyle>

#include <CDockCard.h>
#include <CToolBar.h>

#include <QMDecoratorV2.h>

namespace Core {

    Q_D_LAYOUT_PROPERTY_DECLARE(caption, Caption, captionLayout, ISidePanel)

    CaptionLabel::CaptionLabel(ISidePanel *s, QWidget *parent) : QLabel(parent), s(s) {
    }

    CaptionLabel::~CaptionLabel() {
    }

    void CaptionLabel::mouseDoubleClickEvent(QMouseEvent *event) {
        auto card = s->card();
        if (card->viewMode() == CDockCard::DockPinned) {
            s->card()->toggleMaximizeState();
        }
    }

    ISidePanelPrivate::ISidePanelPrivate() {
        captionWidget = nullptr;
    }

    ISidePanelPrivate::~ISidePanelPrivate() {
    }

    void ISidePanelPrivate::init() {
        Q_Q(ISidePanel);

        captionLayout = new QHBoxLayout();
        captionLayout->setMargin(0);
        captionLayout->setSpacing(0);

        captionLabel = new CaptionLabel(q);
        captionLabel->setObjectName("side-panel-caption-label");

        toolBar = new CToolBar();
        toolBar->setObjectName("side-panel-toolbar");
        toolBar->setLayoutDirection(Qt::RightToLeft);

        captionLayout->addWidget(captionLabel);
        captionLayout->addStretch();
        captionLayout->addWidget(toolBar);

        mainLayout = new QVBoxLayout();
        mainLayout->setMargin(0);
        mainLayout->setSpacing(0);

        mainLayout->addLayout(captionLayout);

        q->setLayout(mainLayout);

        // Init 2
        captionLabel->setText(q->windowTitle());

        // Add basic buttons
        auto closeAction = new QAction(this);
        closeAction->setObjectName("close");
        closeAction->setProperty("caption-button", true);

        auto menuAction = new QAction(this);
        menuAction->setObjectName("menu");
        menuAction->setProperty("caption-button", true);

        toolBar->addAction(closeAction);
        toolBar->addAction(menuAction);

        connect(closeAction, &QAction::triggered, this, &ISidePanelPrivate::_q_closeActionTriggered);
        connect(menuAction, &QAction::triggered, this, &ISidePanelPrivate::_q_menuActionTriggered);

        qIDec->installTheme(q, "core.ISidePanel");
    }

    void ISidePanelPrivate::_q_closeActionTriggered() {
        Q_Q(ISidePanel);
        q->card()->setChecked(false);
    }

    void ISidePanelPrivate::_q_menuActionTriggered() {
        Q_Q(ISidePanel);

        QContextMenuEvent e(QContextMenuEvent::Other, q->card()->mapFromGlobal(QCursor::pos()), QCursor::pos(),
                            QApplication::keyboardModifiers());
        QApplication::sendEvent(q->card(), &e);
    }

    ISidePanel::ISidePanel(IProjectWindow *iWin, QWidget *parent) : ISidePanel(*new ISidePanelPrivate(), iWin, parent) {
    }

    ISidePanel::~ISidePanel() {
    }

    void ISidePanel::initialize() {
    }

    void ISidePanel::extensionInitialized() {
    }

    QToolBar *ISidePanel::toolBar() const {
        Q_D(const ISidePanel);
        return d->toolBar;
    }

    QWidget *ISidePanel::captionWidget() const {
        Q_D(const ISidePanel);
        return d->captionWidget;
    }

    QWidget *ISidePanel::takeCaptionWidget() {
        Q_D(ISidePanel);
        if (d->captionWidget)
            return nullptr;

        auto org = d->captionWidget;
        d->captionWidget = nullptr;

        d->captionLayout->replaceWidget(org, d->captionLabel);
        d->captionLabel->show();

        return org;
    }

    void ISidePanel::setCaptionWidget(QWidget *w) {
        Q_D(ISidePanel);

        if (!d->captionWidget) {
            d->captionLayout->replaceWidget(d->captionLabel, w);
            w->show();
            d->captionLabel->hide();
            return;
        }

        auto &org = d->captionWidget;
        d->captionLayout->replaceWidget(org, w);
        w->show();

        delete org;
        org = nullptr;
    }

    QWidget *ISidePanel::centralWidget() const {
        Q_D(const ISidePanel);
        if (d->mainLayout->count() < 2)
            return nullptr;
        return d->mainLayout->itemAt(1)->widget();
    }

    QWidget *ISidePanel::takeCentralWidget() {
        Q_D(ISidePanel);
        if (d->mainLayout->count() < 2)
            return nullptr;

        auto org = d->mainLayout->itemAt(1)->widget();
        d->mainLayout->removeWidget(org);

        return org;
    }

    void ISidePanel::setCentralWidget(QWidget *w) {
        Q_D(ISidePanel);
        delete takeCentralWidget();
        d->mainLayout->addWidget(w);
    }

    bool ISidePanel::event(QEvent *event) {
        Q_D(ISidePanel);
        switch (event->type()) {
            case QEvent::WindowTitleChange: {
                d->captionLabel->setText(windowTitle());
                break;
            }
            default:
                break;
        }
        return CDockToolWindow::event(event);
    }

    void ISidePanel::viewModeChanged(CDockCard::ViewMode viewMode) {
        switch (viewMode) {
            case CDockCard::DockPinned:
                setProperty("view-mode", "dock-pinned");
                style()->polish(this);
                break;
            case CDockCard::Float:
                setProperty("view-mode", "float");
                style()->polish(this);
                break;
            case CDockCard::Window:
                setProperty("view-mode", "window");
                style()->polish(this);
                setWindowIcon(qApp->windowIcon());
                break;
        }
    }

    ISidePanel::ISidePanel(ISidePanelPrivate &d, IProjectWindow *iWin, QWidget *parent)
        : CDockToolWindow(parent), IPianoRollComponent(iWin), d_ptr(&d) {
        d.q_ptr = this;

        d.init();
    }

}