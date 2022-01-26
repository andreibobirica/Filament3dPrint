#ifndef PIECHARTVIEW_H
#define PIECHARTVIEW_H

#include "view/view.h"

#include <QtCharts/QChartView>
#include <QtCharts/QPieSeries>
#include <QtCharts/QPieSlice>
#include <QHBoxLayout>


QT_CHARTS_USE_NAMESPACE

/**
 * @brief The PieChartView class VIEW della schermata PieChart
 * Mostra un grafico PieChart
 */
class PieChartView : public View
{
    Q_OBJECT
protected:
    QPieSeries* series;
    QChart* chart;

private:
    /**
     * @brief connectViewSignals Metodo virtuale che serve a collegare i segnali dei singoli
     * Widget ai segnali della View
     */
    void connectViewSignals() const override{
        // non ci sono segnali da connettere
    }

public:
    explicit PieChartView(const QSize& s = QSize(800,500),View* parent = nullptr);

    /**
     * @brief insertMaterial Metodo che serve ad inserire un nuovo materiale nel grafico
     * a torta
     * @param materiale materiale da aggiungere
     * @param occurences occorenze del materiale
     */
    virtual void insertMaterial(const QString& materiale, unsigned int occurences);

    /**
     * @brief applyGraphics Metodo che serve ad impostare le caratteristiche grafiche
     * del grafioc a torta
     * In particolare imposta i label visibili, mostra un contorno per ogni fetta
     * e modifica il label aggiungendo la percentuale accanto.
     */
    virtual void applyGraphics();
};

#endif // PIECHARTVIEW_H
