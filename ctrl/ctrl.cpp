#include "ctrl/ctrl.h"

void Ctrl::connectViewCtrlSignalsSlots() const {
    connect(view,SIGNAL(viewClosed()),this,SLOT(onViewClosed()));
}

Ctrl::Ctrl(View* v, Model* m,Ctrl* parent) : view(v), model(m), QObject(parent){
    connectViewCtrlSignalsSlots();
}

View* Ctrl::getView() const {
    return view;
}

Model* Ctrl::getModel() const{return model;}

void Ctrl::showView() const{
    view->show();
}

void Ctrl::hideView() const{
    view->hide();
}
