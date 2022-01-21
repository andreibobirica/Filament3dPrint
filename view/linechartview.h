#ifndef LINECHARTVIEW_H
#define LINECHARTVIEW_H

#include <QtCharts/QChartView>
#include <QtCharts/QLineSeries>
#include <QHBoxLayout>
#include <map>

#include <QDebug>

#include "view/view.h"

QT_CHARTS_USE_NAMESPACE

class LineChartView : public View
{
    Q_OBJECT
private:
    QChart* chart;
    std::map<QString,QLineSeries*> materialsSerie;

    /**
     * @brief connectViewSignals Metodo virtuale che serve a collegare i segnali dei singoli
     * Widget ai segnali della View
     */
    void connectViewSignals() const override{}
public:
    explicit LineChartView(const QSize& size = QSize(800,500), View* parent = nullptr) : View(size,parent){
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

    void insertMaterialRecord(const QString& materiale,const uint durata, const uint consumo){
        if(materialsSerie.find(materiale) == materialsSerie.end()){
            QLineSeries* ls = new QLineSeries();
            ls->append(durata,consumo);
            ls->setName(materiale);
            //ls->setUseOpenGL(true);
            //ls->setPointLabelsVisible(true);    // is false by default
            //ls->setPointLabelsColor(Qt::black);
            //ls->setPointLabelsFormat("@yPoint");
            materialsSerie.insert({materiale,ls});
        }
        materialsSerie[materiale]->append(durata,consumo);

        //ordino la serie
        QVector<QPointF> points = materialsSerie[materiale]->pointsVector();
        std::sort(points.begin(), points.end(), [](const QPointF & p1, const QPointF & p2) {
            return p1.x() > p2.x();
        });
        materialsSerie[materiale]->replace(points);
    }

    void applyChartSeries(){
        chart->removeAllSeries();
        for (const auto& kv : materialsSerie) {
            chart->addSeries(kv.second);
        }
        chart->createDefaultAxes();
    }
};

#endif // LINECHARTVIEW_H
