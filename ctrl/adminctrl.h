#ifndef ADMINCTRL_H
#define ADMINCTRL_H

#include <list>

#include "ctrl/ctrl.h"
#include "view/adminview.h"


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
     * @param m Model collegato al Controller
     */
    explicit AdminCtrl(View* v, Model* m = new Model(), Ctrl* parent = nullptr);

    /**
     * @brief getView Ritorna La View castata almeno al tipo AdminView
     * @return
     */
    AdminView* getView() const override;

    /**
     * @brief getModel Ritorna il Model castato almeno al tipo ModelView
     * @return
     */
    AdminModel* getModel() const override;

signals:

public slots:
     void onViewClosed() const override;
     void onRecordTableRemoved(unsigned int row);
     void onRecordTableAdded(const QString& m, unsigned int d, unsigned int mu, const QDate& da);
};

#endif // ADMINCTRL_H
