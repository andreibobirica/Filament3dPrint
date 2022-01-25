#ifndef BARCHARTVIEW_H
#define BARCHARTVIEW_H

#include <QtCharts/QChartView>
#include <QtCharts/QBarSeries>
#include <QtCharts/QBarSet>
#include <QtCharts/QLegend>
#include <QtCharts/QBarCategoryAxis>
#include <QtCharts/QValueAxis>

#include <QHBoxLayout>
#include <QDebug>

#include <map>
#include <list>

#include "view/view.h"

QT_CHARTS_USE_NAMESPACE

class BarChartView : public View
{
    Q_OBJECT
private:
    QChart* chart;
    QBarSeries *series;
    std::list<QBarSet*>(listaSetsMateriali);
    QStringList listaMesi;

    /**
     * @brief connectViewSignals Metodo virtuale che serve a collegare i segnali dei singoli
     * Widget ai segnali della View
     */
    void connectViewSignals() const override;

public:
    /**
     * @brief BarChartView Costruttore della View
     * @param size size della window
     * @param parent view parente invocante
     */
    explicit BarChartView(const QSize& size = QSize(800,500), View* parent = nullptr);

    /**
     * @brief insertSetMateriale Metodo che serve ad inserire un SET di dati
     * Un set di dati in questo caso rappresenta una barra e per ciascuna meseA
     * cioè ciascuna data.
     * @param materiale materiale titolo del set
     * @param consumiMesi consumi per ogni meseA del set, per ogni barra
     */
    void insertSetMateriale(const QString& materiale, std::list<uint> consumiMesi);

    /**
     * @brief applySetsOnChart Metodo che aggiunge i sets allla series
     * successivemente applica la series al chart.
     * in pratica mostra i dati al chart.
     */
    void applySetsOnChart();

    /**
     * @brief applyAxis Metodo che imposta i dettagli degli Assi
     * impostandone la grandezza e la descrizione
     * @param mesi lista dei meseA con la descrizione per l'asse X
     * @param maxY massimo intero dei dati da rapresentare, appunto con la
     * granzza massima del asse y
     */
    void applyAxis(const QStringList& mesi, const uint maxY);
};

#endif // BARCHARTVIEW_H
