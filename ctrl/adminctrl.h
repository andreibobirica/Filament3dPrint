#ifndef ADMINCTRL_H
#define ADMINCTRL_H

#include <ctrl.h>
/**
 * @brief The AdminCtrl class
 * AdminCtrl classe derivata da Ctrl ossia un Controller specializzato della schermata Admin della applicazione
 */
class AdminCtrl : public Ctrl
{
public:
    /**
     * @brief AdminCtrl
     * @param v View collegata al Controller
     */
    AdminCtrl(View* v);
};

#endif // ADMINCTRL_H
