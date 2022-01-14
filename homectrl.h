#ifndef HOMECTRL_H
#define HOMECTRL_H

#include <ctrl.h>

/**
 * @brief The HomeCtrl class
 * Classe Derivata da Ctrl, è il Controller specifico per la View HomeView
 * Serve a controllare tutto quello che riguarda la schermata Home della App
 */
class HomeCtrl : public Ctrl
{
public:
    /**
     * @brief HomeCtrl
     * @param v View collegata al Controller
     */
    HomeCtrl(View* v);
};

#endif // HOMECTRL_H
