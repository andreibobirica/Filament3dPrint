#include "barchartview.h"

void BarChartView::connectViewSignals() const{
    //niente da dichiarare
}

BarChartView::BarChartView(const QSize &size, View *parent) :
    View(size,parent),
    chart(new QChart()),
    series(new QBarSeries())
{
    //Connetto i segnali della View ai widget
    connectViewSignals();


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

void BarChartView::insertSetMateriale(const QString &materiale, std::list<uint> consumiMesi){
    QBarSet* set = new QBarSet(materiale);
    for(auto consumiMese : consumiMesi)
        *set << consumiMese;
    listaSetsMateriali.push_back(set);
}

void BarChartView::applySetsOnChart(){
    for(auto s : listaSetsMateriali)
        series->append(s);
    chart->addSeries(series);
}

void BarChartView::applyAxis(const QStringList &mesi, const uint maxY){
    QBarCategoryAxis *axisX = new QBarCategoryAxis();
    axisX->append(mesi);
    chart->addAxis(axisX, Qt::AlignBottom);
    series->attachAxis(axisX);

    QValueAxis *axisY = new QValueAxis();
    axisY->setRange(0,maxY);
    chart->addAxis(axisY, Qt::AlignLeft);
    series->attachAxis(axisY);

    //Imposto titolo degli assi
    if(chart->axisX() && chart->axisY()){
       chart->axisX()->setTitleText("Mese-Anno");
       chart->axisY()->setTitleText("Consumo Totale Mensile(g)");
    }
}
