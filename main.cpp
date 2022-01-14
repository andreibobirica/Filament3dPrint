#include "ctrl/adminctrl.h"
#include "ctrl/homectrl.h"
#include "view/homeview.h"
#include "view/adminview.h"

#include <QSize>

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    HomeView* homeView = new HomeView(new QSize(1000,1000));
    HomeCtrl* homeCtrl = new HomeCtrl(homeView);
    homeCtrl->showView();

    AdminCtrl* adminCtrl = new AdminCtrl(new AdminView);
    adminCtrl->showView();

    return a.exec();
}
