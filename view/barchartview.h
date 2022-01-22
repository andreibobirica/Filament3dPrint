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
    QBarCategoryAxis* axeX;
    std::map<QString,QBarSet*> materialSets;

    /**
     * @brief connectViewSignals Metodo virtuale che serve a collegare i segnali dei singoli
     * Widget ai segnali della View
     */
    void connectViewSignals() const override{
        // non ci sono segnali da connettere
    }

public:
    explicit BarChartView(const QSize& size = QSize(800,500), View* parent = nullptr) : View(size,parent){
        QHBoxLayout* mainLayout = new QHBoxLayout;
        chart = new QChart();
        chart->setTheme(QChart::ChartThemeDark);
        chart->setAnimationOptions(QChart::AllAnimations);
        chart->setAnimationDuration(1500);
        chart->legend()->setVisible(true);
        chart->legend()->setAlignment(Qt::AlignBottom);
        chart->setTitle("TITOLO TITOLO TITOTLO");

       // chart->setAxisX(axis, series);

        QChartView *chartView = new QChartView(chart,this);
        chartView->setRenderHint(QPainter::Antialiasing);
        mainLayout->addWidget(chartView);
        setLayout(mainLayout);
        setMinimumSize(800,500);
        resize(size);


        //![2]
        series = new QBarSeries();
        //![2]

        //![3]
        chart->addSeries(series);
        //![3]

        //![4]
        //!
        //!
        QValueAxis *axisY = new QValueAxis();
        axisY->setRange(0,15);
        chart->addAxis(axisY, Qt::AlignLeft);
        series->attachAxis(axisY);

        //![4]

        //![5]

        insertMaterialSet(tr("PLA"),{1,2,23,5,13,4});
        applyChartSeries();
        insertMensilità({"m1","m2","m3","m3ì4"});
        insertMensilità({"m12","m2","m3","m3ì4"});
    }

    void insertMaterialSet(const QString& materiale,std::list<uint> consumiMensili){
        if(materialSets.find(materiale) == materialSets.end()){
            materialSets[materiale] = new QBarSet(materiale);
        }
        for(const uint& consumo : consumiMensili){
            materialSets[materiale]->append(consumo);
        }
    }

    void insertMensilità(const QStringList& listaMeseAnno){
        if(axeX){
            chart->removeAxis(axeX);
            series->detachAxis(axeX);
        }

        axeX =  new QBarCategoryAxis();
        for(const auto& meseAnno : listaMeseAnno){
            axeX->append(meseAnno);
        }

        chart->addAxis(axeX, Qt::AlignBottom);
        series->attachAxis(axeX);
    }

    void applyChartSeries(){
        for(const auto& kv : materialSets) {
            series->append(kv.second);
        }

        chart->removeSeries(series);
        chart->addSeries( series );
        chart->createDefaultAxes();
        //chart->setAxisX(axeX, series);
    }

};

#endif // BARCHARTVIEW_H
