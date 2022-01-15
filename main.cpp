#include "ctrl/adminctrl.h"
#include "ctrl/homectrl.h"
#include "view/homeview.h"
#include "view/adminview.h"

#include <QSize>

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    HomeView* homeView = new HomeView(new QSize(720,720));
    HomeCtrl* homeCtrl = new HomeCtrl(homeView);
    homeCtrl->showView();

    AdminView* adminView = new AdminView(new QSize(720,720));
    AdminCtrl* adminCtrl = new AdminCtrl(adminView);
    adminCtrl->showView();

    return a.exec();
}
