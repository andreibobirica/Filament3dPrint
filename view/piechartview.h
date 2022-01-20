#ifndef PIECHARTVIEW_H
#define PIECHARTVIEW_H

#include "view/view.h"

#include <QtCharts/QChartView>
#include <QtCharts/QPieSeries>
#include <QtCharts/QPieSlice>
#include <QHBoxLayout>

QT_CHARTS_USE_NAMESPACE


class PieChartView : public View
{
private:
    void connectViewSignals() const override{}
public:
    PieChartView(View* parent = nullptr){
        QHBoxLayout* mainLayout = new QHBoxLayout;


        QPieSeries* series = new QPieSeries();
        series->append("Jane", 1);
        series->append("Joe", 2);
        series->append("Andy", 3);
        series->append("Barbara", 5);
        series->append("Axel", 10);

        QPieSlice* slice = series->slices().at(1);
        slice->setExploded();
        slice->setLabelVisible();
        slice->setPen(QPen(Qt::darkGreen, 2));
        slice->setBrush(Qt::green);

        slice = series->slices().at(3);
        //slice->setExploded();
        slice->setLabelVisible();
        slice->setPen(QPen(Qt::darkGreen, 5));
        slice->setBrush(Qt::green);


        QChart* chart = new QChart();
        chart->addSeries(series);
        chart->setTitle("Simple piechart example");
        //chart->legend()->hide();

        QChartView *chartView = new QChartView(chart);
        chartView->setRenderHint(QPainter::Antialiasing);
        mainLayout->addWidget(chartView);
        setLayout(mainLayout);
        resize(800,900);
        show();
    }
};

#endif // PIECHARTVIEW_H
