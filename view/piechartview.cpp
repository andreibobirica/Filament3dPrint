#include "piechartview.h"

PieChartView::PieChartView(const QSize& size,View *parent) : View(size,parent), series(new QPieSeries()), chart(new QChart()){
    QHBoxLayout* mainLayout = new QHBoxLayout;
    chart->addSeries(series);
    QChartView *chartView = new QChartView(chart,this);
    chartView->setRenderHint(QPainter::Antialiasing);
    mainLayout->addWidget(chartView);
    setLayout(mainLayout);
    setMinimumSize(800,600);
    resize(800,900);
}

void PieChartView::insertMaterial(const QString &materiale, unsigned int occurences){
    series->append(materiale+tr(" N: ")+QString::number(occurences), occurences);
}

void PieChartView::applyGraphics(){
    for(QPieSlice* slice : series->slices()){
        //slice->setExploded();
        slice->setLabelVisible();
        slice->setPen(QPen(Qt::darkGreen, 2));
        slice->setLabelColor(Qt::white);
    }
    chart->setTitle("Consumo numerico per ogni Materiale usato");
    series->setLabelsPosition(QPieSlice::LabelInsideHorizontal);
}
