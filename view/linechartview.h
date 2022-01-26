#ifndef LINECHARTVIEW_H
#define LINECHARTVIEW_H

#include "view/view.h"

#include <QtCharts/QChartView>
#include <QtCharts/QSplineSeries>
#include <QHBoxLayout>
#include <map>

QT_CHARTS_USE_NAMESPACE

class LineChartView : public View
{
    Q_OBJECT
private:
    QChart* chart;
    std::map<QString,QSplineSeries*> materialsSerie;

    /**
     * @brief connectViewSignals Metodo virtuale che serve a collegare i segnali dei singoli
     * Widget ai segnali della View
     */
    void connectViewSignals() const override{
        // non ci sono segnali da connettere
    }
public:
    /**
     * @brief LineChartView  Costruttore della View LineChart
     * @param size Grandezza della schermata
     * @param parent padre(view) della vista che ha invocato la suddetta vista
     */
    explicit LineChartView(const QSize& size = QSize(800,500), View* parent = nullptr);

    /**
     * @brief insertMaterialRecord Metodo che serve ad inserire i dati relativi ad una singola
     * stampa, questi dati saranno elaborati e per ciascun materiale sarà creata una linea.
     * La linea viene rappresentata da un insieme di punti detto QLineSeries.
     * Se la linea non esiste viene prima creata, se la linea esiste giò ci viene aggiunto un
     * punto.
     * @param materiale Materiale identificante la linea
     * @param durata durata della stampa (asse X)
     * @param consumo consumo della stampa (asse Y)
     */
    void insertMaterialData(const QString& materiale,const uint durata, const uint consumo);

    /**
     * @brief applyChartSeries Metodo che applica le serie create (insieme di linee) e le
     * mostra al grafico chart.
     * Questo metodo serve perchè il LineChart ha bisogno prima dei dati e poi di mostrare il grafico.
     */
    void applyChartSeries();
};

#endif // LINECHARTVIEW_H
