#include "barchartoldview.h"

BarChartOldView::BarChartOldView(const QSize &size, View *parent) :
    BarChartView(size,parent){
    //Tema high contrast per un effetto antico della vista
    chart->setTheme(QChart::ChartThemeHighContrast);
    //Imposto di mostrare solamente 3 mesi alla volta
    maxVisMesi = 3;
}
