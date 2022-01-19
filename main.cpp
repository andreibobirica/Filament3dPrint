#include "ctrl/adminctrl.h"
#include "ctrl/homectrl.h"
#include "view/homeview.h"
#include "view/adminview.h"

#include <QSize>
#include <QDebug>

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    HomeView* homeView = new HomeView();
    HomeCtrl* homeCtrl = new HomeCtrl(homeView);
    homeCtrl->showView();

    return a.exec();
}
