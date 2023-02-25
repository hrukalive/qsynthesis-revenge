#ifndef PLAINWINDOWPRIVATE_H
#define PLAINWINDOWPRIVATE_H

#include <QPluginLoader>

#include "../PlainWindow.h"
#include "Api/IWindowHandle.h"

#include "QsFrameworkGlobal.h"

class QSFRAMEWORK_API PlainWindowPrivate {
    Q_DECLARE_PUBLIC(PlainWindow)
public:
    PlainWindowPrivate();
    virtual ~PlainWindowPrivate();

    void init();

    PlainWindow *q_ptr;

#ifndef Q_OS_MAC
    QPluginLoader *loader;
    QsApi::IWindowHandle *winHandle;
#endif
};

#endif // PLAINWINDOWPRIVATE_H