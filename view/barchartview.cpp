#include "barchartview.h"

void BarChartView::connectViewSignals() const{
    //niente da dichiarare
}

BarChartView::BarChartView(const QSize &size, View *parent) :
    View(size,parent),
    chart(new QChart()),
    series(new QBarSeries()),
    chartScroll(new QScrollBar(Qt::Horizontal,this))
{
    //Connetto i segnali della View ai widget
    connectViewSignals();

    //Chart
    chart->setTheme(QChart::ChartThemeDark);
    chart->setAnimationOptions(QChart::SeriesAnimations);
    chart->setAnimationDuration(1500);
    chart->legend()->setVisible(true);
    chart->legend()->setAlignment(Qt::AlignBottom);
    chart->setTitle("Consumo Totale Mensile");
    QChartView* chartView = new QChartView(chart,this);
    chartView->setRenderHint(QPainter::Antialiasing);

    //Main Layout
    QVBoxLayout* mainLayout = new QVBoxLayout;
    mainLayout->addWidget(chartView);
    mainLayout->addWidget(chartScroll);
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
    //Set range per il grafico, massimo 6 mesi PER volta da mostrare
    //Se il numero di mesi disponibili è più grande di 6 imposto un range dal primo al 6 mese
    //Se il numero di mesi disponibile è più piccolo di 6 imposto un range dal primo al ultimo
    axisX->setRange(mesi.at(0),mesi.length() > maxVisMesi  ? mesi.at(maxVisMesi-1) : mesi.last());
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

    //Scrlling
    //Imposto il range della scrllbar da 0 al mesiA.lenght - mesiVisibili
    //il range finisce a mesiA.lenght - mesiVisibili perchè così
    //posso mostrare da v a v+mesivisibili
    chartScroll->setRange(0,mesi.length()-(maxVisMesi));
    //Creo una connessione per la scrllbar in maniera che al variare del suo valore
    //mostro sul cahrt a partire da valore selezionato a valore selezionato + mesi visibili
    int max = maxVisMesi;
    connect(chartScroll,&QAbstractSlider::valueChanged,this,[max,mesi,this](int v){
        chart->axisX()->setRange(mesi.at(v),mesi.at(v+(max-1)));
    });
}


