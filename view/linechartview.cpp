#include "linechartview.h"

LineChartView::LineChartView(const QSize &size, View *parent) : View(size,parent){
    QHBoxLayout* mainLayout = new QHBoxLayout;
    chart = new QChart();
    chart->setTitle("Rapporto Durata Consumo");
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

void LineChartView::insertMaterialData(const QString &materiale, const uint durata, const uint consumo){
    if(materialsSerie.find(materiale) == materialsSerie.end()){
        QSplineSeries* ls = new QSplineSeries();
        ls->append(durata,consumo);
        ls->setName(materiale);
        materialsSerie.insert({materiale,ls});
    }
    materialsSerie[materiale]->append(durata,consumo);

    //ordino la serie
    QVector<QPointF> points = materialsSerie[materiale]->pointsVector();
    std::sort(points.begin(), points.end(), [](const QPointF & p1, const QPointF & p2) {
        return p1.x() < p2.x();
    });
    materialsSerie[materiale]->replace(points);
}

void LineChartView::applyChartSeries(){
    chart->removeAllSeries();
    for (const auto& kv : materialsSerie) {
        chart->addSeries(kv.second);
    }
    chart->createDefaultAxes();
    if(chart->axisX() && chart->axisY()){
       chart->axisX()->setTitleText("Durata Stampa (h)");
       chart->axisY()->setTitleText("Consumo Stampa (g)");
    }
}
