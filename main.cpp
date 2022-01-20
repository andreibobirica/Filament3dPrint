#include "ctrl/adminctrl.h"
#include "ctrl/homectrl.h"
#include "view/homeview.h"

#include "view/piechartview.h"

#include <QSize>
#include <QDebug>

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    a.setWindowIcon(QIcon("./myicon.ico"));

    HomeView* homeView = new HomeView();
    HomeCtrl* homeCtrl = new HomeCtrl(homeView);
    homeCtrl->showView();

    PieChartView* pc = new PieChartView();

    return a.exec();
}
