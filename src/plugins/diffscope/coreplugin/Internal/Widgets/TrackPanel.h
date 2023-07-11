#ifndef CHORUSKIT_TRACKPANEL_H
#define CHORUSKIT_TRACKPANEL_H

#include <QFrame>

#include "PianoRoll/ISidePanel.h"

namespace Core::Internal {

    class TrackPanel : public ISidePanel {
        Q_OBJECT
    public:
        explicit TrackPanel(IProjectWindow *iWin, QWidget *parent = nullptr);
        ~TrackPanel();

        void initialize() override;
        void extensionInitialized() override;
    };

}



#endif // CHORUSKIT_TRACKPANEL_H
