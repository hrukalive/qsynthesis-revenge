#ifndef HOMERECENTWIDGET_H
#define HOMERECENTWIDGET_H

#include <QButtonGroup>
#include <QFrame>
#include <QHash>
#include <QLineEdit>
#include <QSplitter>
#include <QVBoxLayout>

#include "CTabButton.h"
#include "Layout/QMEqualBoxLayout.h"
#include "QPixelSize.h"
#include "Widgets/FileListWidget.h"
#include "Widgets/LinearScrollArea.h"

#include "Interfaces/IButtonBar.h"

namespace Core {

    class HomeRecentTopButtonBar;

    /**
     * @brief Recent widget top frame
     */
    class HomeRecentTopFrame : public QFrame {
        Q_OBJECT
        Q_LAYOUT_PROPERTY_DELCARE
    public:
        explicit HomeRecentTopFrame(QWidget *parent = nullptr);
        ~HomeRecentTopFrame();

    public:
        void reloadStrings();

        Q_INVOKABLE QAbstractButton *addButton(const QString &id);
        Q_INVOKABLE void removeButton(const QString &id);

        IButtonBar *buttonBar() const;

    signals:
        void newRequested();
        void openRequested();

    private:
        CTabButton *newButton;
        CTabButton *openButton;
        QLineEdit *searchBox;

        QMEqualBoxLayout *topLayout;
        QHash<QString, QAbstractButton *> externButtons;

        // Interfaces
        HomeRecentTopButtonBar *m_buttonBar;

        friend class HomeRecentWidget;
    };

    /**
     * @brief Recent widget
     */
    class HomeRecentWidget : public QSplitter {
        Q_OBJECT
    public:
        explicit HomeRecentWidget(QWidget *parent = nullptr);
        ~HomeRecentWidget();

        void reloadStrings();

        HomeRecentTopFrame *topWidget;
        LinearScrollArea *bottomWidget;

        QsApi::FileListWidget *fileWidget;

    private:
        void _q_searchTextChanged(const QString &text);
    };

} // Core

#endif // HOMERECENTWIDGET_H