#ifndef HOMECTRL_H
#define HOMECTRL_H

#include "ctrl/ctrl.h"
#include "view/homeview.h"

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

    HomeView* getView() const override{
        return static_cast<HomeView*>(Ctrl::getView());
    }
};

#endif // HOMECTRL_H
