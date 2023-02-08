#ifndef DSSTARTINFOPRIVATE_H
#define DSSTARTINFOPRIVATE_H

#include "../DsStartInfo.h"
#include "private/QsStartInfo_p.h"

#include "Managers/WindowManager.h"

class DsStartInfoPrivate : public QsStartInfoPrivate {
    Q_DECLARE_PUBLIC(DsStartInfo)
public:
    DsStartInfoPrivate();
    ~DsStartInfoPrivate();

    void init();
    void load_helper();
    void deinit();

    WindowManager *windowMgr;

private:
    CDecorateDir dd;
    CDecorateDir dd_gui;
};

#endif // DSSTARTINFOPRIVATE_H