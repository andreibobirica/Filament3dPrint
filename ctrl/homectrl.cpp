#include "ctrl/homectrl.h"

HomeCtrl::HomeCtrl(View* v,Ctrl* parent) : Ctrl(v,nullptr,parent){
    //Collego i SIGNAL della View Ai SLOT del Controller
    connectViewCtrlSignalsSlots();

}

HomeView* HomeCtrl::getView() const{
    return static_cast<HomeView*>(Ctrl::getView());
}


void HomeCtrl::connectViewCtrlSignalsSlots() const{
    connect(getView(),SIGNAL(newProject()),this,SLOT(onNewProject()));
    connect(getView(),SIGNAL(openProject()),this,SLOT(onOpenProject()));
}

void HomeCtrl::onNewProject() const{
    qDebug("new Project");

    AdminView* adminView = new AdminView(new QSize(720,720),getView());
    AdminCtrl* adminCtrl = new AdminCtrl(adminView,nullptr,const_cast<HomeCtrl*>(this));
    adminCtrl->showView();
    //static_cast<View*>(adminView->parent())->hide();
    //static_cast<View*>(adminView->parent())->show();
    //getView()->close();
}

void HomeCtrl::onOpenProject() const{
    qDebug("open Project");
}
