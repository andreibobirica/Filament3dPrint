#include "ctrl/adminctrl.h"

AdminCtrl::AdminCtrl(View* v, Model* m, Ctrl* parent) : Ctrl(v,m,parent){
    //Collego i SIGNAL della View Ai SLOT del Controller
    connectViewCtrlSignalsSlots();
}

void AdminCtrl::connectViewCtrlSignalsSlots() const{}

void AdminCtrl::onViewClosed() const {
    delete this;
}
