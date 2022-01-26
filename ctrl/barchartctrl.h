#ifndef BARCHARTCTRL_H
#define BARCHARTCTRL_H

#include "ctrl/ctrl.h"

#include "view/barchartview.h"
#include "model/barchartmodel.h"

/**
 * @brief The BarChartCtrl class
 * BarChartCtrl classe derivata da Ctrl ossia un Controller specializzato della schermata BarChart della applicazione
 */
class BarChartCtrl : public Ctrl
{
    Q_OBJECT
public:
    /**
     * @brief BarChartCtrl Costruttore del Controller per la schermata
     * bar chart
     * @param v view
     * @param m model
     * @param parent controller padre
     */
    explicit BarChartCtrl(BarChartView* v,BarChartModel* m, Ctrl* parent = nullptr);

    /**
     * @brief getView metodo virtuale che restituisce il campo view castato
     * al tipo corrente BarChartView
     * @return view
     */
    BarChartView* getView() const override;
    /**
     * @brief getModel metodo virtuale che restituisce il campo model castato
     * al tipo corrente BarChartModel
     * @return
     */
    BarChartModel* getModel() const override;

    /**
     * @brief showView Metodo overriding
     * mostra la view, in questo caso oltre a mostrare la view
     * emette anche un popup dialog in cui informa l'utente che sta
     * per visualizzare i dati
     */
    void showView() const override;

public slots:
    /**
     * @brief onViewClosed Metodo virtuale che definisce il cosa fare alla chiusura della schermata
     * in questo caso NIENTE, distrugge solamente il costruttore
     */
    void onViewClosed() const override;


};

#endif // BARCHARTCTRL_H
