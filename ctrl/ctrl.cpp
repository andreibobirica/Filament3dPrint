#include "ctrl/ctrl.h"

void Ctrl::connectViewCtrlSignalsSlots() const {
    connect(view,SIGNAL(viewClosed()),this,SLOT(onViewClosed()));
}

Ctrl::Ctrl(View* v, Model* m,Ctrl* parent) : QObject(parent), view(v), model(m){
    connectViewCtrlSignalsSlots();
}

Ctrl::~Ctrl() {
    setParent(nullptr);
    for(auto child : children())
        delete child;
    delete view; delete model;
}

void Ctrl::showView() const{
    view->show();
}

void Ctrl::hideView() const{
    view->hide();
}
