#include "piechartview.h"

PieChartView::PieChartView(const QSize& size,View *parent) : View(size,parent), series(new QPieSeries()), chart(new QChart()){
    QHBoxLayout* mainLayout = new QHBoxLayout;
    chart->addSeries(series);
    chart->legend()->setVisible(true);
    chart->legend()->setAlignment(Qt::AlignBottom);
    chart->setTheme(QChart::ChartThemeDark);
    chart->setAnimationOptions(QChart::AllAnimations);
    chart->setAnimationDuration(1500);
    QChartView *chartView = new QChartView(chart,this);
    chartView->setRenderHint(QPainter::Antialiasing);
    mainLayout->addWidget(chartView);
    setLayout(mainLayout);
    setMinimumSize(800,500);
    resize(size);
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
    chart->setTitle("Materiale Usato - Numero volte");
    series->setLabelsPosition(QPieSlice::LabelInsideHorizontal);
}
