#ifndef HOMECTRL_H
#define HOMECTRL_H

#include <QtDebug>

#include "ctrl/ctrl.h"
#include "view/homeview.h"

/**
 * @brief The HomeCtrl class
 * Classe Derivata da Ctrl, è il Controller specifico per la View HomeView
 * Serve a controllare tutto quello che riguarda la schermata Home della App
 */
class HomeCtrl : public Ctrl
{
    Q_OBJECT
public:
    /**
     * @brief HomeCtrl
     * @param v View collegata al Controller
     */
    HomeCtrl(View* v);

    /**
     * @brief getView
     * Metodo virtuale che restituisce la View del controller castata al tipo corretto
     * @return VIEW del Controller interpretata come HomeView
     */
    HomeView* getView() const override;

signals:
public slots:
    void onNewPButtonClicked() const{
        qDebug() << "EVVIVA funziona";
    }
};

#endif // HOMECTRL_H
