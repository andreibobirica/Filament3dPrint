#ifndef LINECHARTCTRL_H
#define LINECHARTCTRL_H

#include "ctrl/ctrl.h"

#include "view/linechartview.h"
#include "model/adminmodel.h"

/**
 * @brief The LineChartCtrl class Classe rappresentante il Controller della schermata
 * LineChart.
 * Si occupa di mostrare sulla sua view LineChartView il modello AdminModel.
 */
class LineChartCtrl : public Ctrl
{
    Q_OBJECT
public:
    /**
     * @brief LineChartCtrl Costruttore che imposta la view il modello
     * Successivamete dal modello prende la recordList e inserisce all'interno della view
     * i dati di ciascun record.
     * @param v view
     * @param m model
     * @param parent Ctrl padre invocante
     */
    explicit LineChartCtrl(LineChartView* v,AdminModel* m, Ctrl* parent = nullptr);

    /**
     * @brief getView metodo virtuale che restituisce il campo view castato
     * al tipo corrente LineChartView
     * @return view
     */
    LineChartView* getView() const override;

    /**
     * @brief getModel metodo virtuale che restituisce il campo model castato
     * al tipo corrente AdminModel
     * @return
     */
    AdminModel* getModel() const override;

public slots:
    /**
     * @brief onViewClosed Metodo virtuale che definisce il cosa fare alla chiusura della schermata
     * in questo caso NIENTE, distrugge solamente il costruttore
     */
    void onViewClosed() const override;
};

#endif // LINECHARTCTRL_H
