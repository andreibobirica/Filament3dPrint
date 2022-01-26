#ifndef PIECHARTCTRL_H
#define PIECHARTCTRL_H

#include "ctrl/ctrl.h"

#include "view/piechartview.h"
#include "model/piechartmodel.h"

/**
 * @brief The PieChartCtrl class Controller della schermata PieChart
 * Si occupa di elaborare i dati dal model e mostrarli sulla view
 */
class PieChartCtrl : public Ctrl
{
    Q_OBJECT
public:
    /**
     * @brief PieChartCtrl Costruttore che si occupa di creare un controller
     * per la piechart schermata
     * @param v view
     * @param m model
     * @param parent Controller parent
     */
    PieChartCtrl(PieChartView* v, PieChartModel* m, Ctrl* parent = nullptr);

    /**
     * @brief getView Metodo virtuale che restituisce la view al tipo corrente PieChartvIEW
     * @return VIEW
     */
    PieChartView* getView() const override;

    /**
     * @brief getModel Metodo virtuale che restituisce il model al tipo corrente PieChartModel
     * @return Model
     */
    PieChartModel* getModel() const override;

public slots:
    /**
     * @brief onViewClosed Metodo virtuale che definisce il cosa fare alla chiusura della schermata
     * in questo caso NIENTE, distrugge solamente il costruttore
     */
    void onViewClosed() const override;
};

#endif // PIECHARTCTRL_H
