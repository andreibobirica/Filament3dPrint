#include "piechartview.h"

PieChartView::PieChartView(const QSize& size,View *parent) : View(size,parent), series(new QPieSeries()), chart(new QChart()){
    QHBoxLayout* mainLayout = new QHBoxLayout;

    series->setLabelsPosition(QPieSlice::LabelInsideHorizontal);
    chart->addSeries(series);
    chart->setTitle("Consumo percentuale per ogni Materiale usato");

    QChartView *chartView = new QChartView(chart,this);
    chartView->setRenderHint(QPainter::Antialiasing);
    mainLayout->addWidget(chartView);
    setLayout(mainLayout);
    setMinimumSize(500,500);
    resize(800,900);
}

void PieChartView::insertMaterial(const QString &materiale, unsigned int occurences){
    series->append(materiale, occurences);
}

void PieChartView::applyGraphics(){
    for(QPieSlice* slice : series->slices()){
        //slice->setExploded();
        slice->setLabelVisible();
        slice->setPen(QPen(Qt::darkGreen, 2));
        slice->setLabel(slice->label() + tr(" ") + QString::number((slice->percentage()*100),'f',1) + " %");
        //slice->setBrush(Qt::green);
    }
}
