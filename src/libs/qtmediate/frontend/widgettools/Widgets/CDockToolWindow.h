#ifndef CDOCKTOOLWINDOW_H
#define CDOCKTOOLWINDOW_H

#include <QFrame>
#include <QMenu>

#include "CDockCard.h"
#include "QMWidgetToolsGlobal.h"

class CDockToolWindowPrivate;

class QMWTOOLS_EXPORT CDockToolWindow : public QFrame {
    Q_OBJECT
    Q_PROPERTY(QMargins resizeMargins READ resizeMargins WRITE setResizeMargins NOTIFY resizeMarginsChanged)
    Q_DECLARE_PRIVATE(CDockToolWindow)
public:
    explicit CDockToolWindow(QWidget *parent = nullptr);
    ~CDockToolWindow();

public:
    QMargins resizeMargins() const;
    void setResizeMargins(const QMargins &resizeMargins);

    void addHitTestVisibleWidget(QWidget *w);
    void removeHitTestVisibleWidget(QWidget *w);

    CDockCard *card() const;
    virtual QMenu *createCardMenu() const;

protected:
    virtual void viewModeChanged(CDockCard::ViewMode viewMode);

signals:
    void resizeMarginsChanged();

protected:
    CDockToolWindow(CDockToolWindowPrivate &d, QWidget *parent = nullptr);

    QScopedPointer<CDockToolWindowPrivate> d_ptr;

    friend class CDockCard;
};

#endif // CDOCKTOOLWINDOW_H