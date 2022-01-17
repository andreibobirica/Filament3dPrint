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
private:

    /**
     * @brief connectViewCtrlSignalsSlots Metodo virtuale
     * Questo Metodo serve a connettere i SIGNAL della AdminView ai Slot del AdminCtrl
     */
    void connectViewCtrlSignalsSlots() const override;

public:
    /**
     * @brief AdminCtrl
     * @param v View collegata al Controller
     */
    explicit AdminCtrl(View* v, Model* m = nullptr, Ctrl* parent = nullptr);

signals:

public slots:
     void onViewClosed() const override;
};

#endif // ADMINCTRL_H
