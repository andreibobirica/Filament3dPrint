#ifndef ADMINCTRL_H
#define ADMINCTRL_H

#include "ctrl/ctrl.h"
/**
 * @brief The AdminCtrl class
 * AdminCtrl classe derivata da Ctrl ossia un Controller specializzato della schermata Admin della applicazione
 */
class AdminCtrl : public Ctrl
{
    Q_OBJECT
public:
    /**
     * @brief AdminCtrl
     * @param v View collegata al Controller
     */
    AdminCtrl(View* v);

signals:

public slots:

};

#endif // ADMINCTRL_H
