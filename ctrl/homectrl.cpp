#include "ctrl/homectrl.h"

HomeCtrl::HomeCtrl(View* v) : Ctrl(v){
    connect(getView(),SIGNAL(newPButtonClicked()),this,SLOT(onNewPButtonClicked()));
}

HomeView* HomeCtrl::getView() const{
    return static_cast<HomeView*>(Ctrl::getView());
}
