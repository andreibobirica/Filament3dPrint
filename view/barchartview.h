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
    void connectViewSignals() const override{
        // non ci sono segnali da connettere
    }

public:
    explicit BarChartView(const QSize& size = QSize(800,500), View* parent = nullptr) :
            View(size,parent),
            chart(new QChart()),
            series(new QBarSeries())
    {
        chart->setTheme(QChart::ChartThemeDark);
        chart->setAnimationOptions(QChart::AllAnimations);
        chart->setAnimationDuration(1500);
        chart->legend()->setVisible(true);
        chart->legend()->setAlignment(Qt::AlignBottom);
        chart->setTitle("Consumo Totale Mensile");
        QChartView *chartView = new QChartView(chart,this);
        chartView->setRenderHint(QPainter::Antialiasing);
        QHBoxLayout* mainLayout = new QHBoxLayout;
        mainLayout->addWidget(chartView);
        setLayout(mainLayout);
        setMinimumSize(800,500);
        resize(size);
    }

    void insertSetMateriale(const QString& materiale, std::list<uint> consumiMesi){
        QBarSet* set = new QBarSet(materiale);
        for(auto consumiMese : consumiMesi)
            *set << consumiMese;
        listaSetsMateriali.push_back(set);
    }

    void applySetsOnChart(){
        for(auto s : listaSetsMateriali)
            series->append(s);
        chart->addSeries(series);
    }

    void applyAxis(const QStringList& mesi, const uint maxY){
        QBarCategoryAxis *axisX = new QBarCategoryAxis();
        axisX->append(mesi);
        chart->addAxis(axisX, Qt::AlignBottom);
        series->attachAxis(axisX);

        QValueAxis *axisY = new QValueAxis();
        axisY->setRange(0,maxY);
        chart->addAxis(axisY, Qt::AlignLeft);
        series->attachAxis(axisY);
    }
};

#endif // BARCHARTVIEW_H
