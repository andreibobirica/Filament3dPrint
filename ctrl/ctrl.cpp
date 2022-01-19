#include "ctrl/ctrl.h"

Ctrl::Ctrl(View* v, Model* m,Ctrl* parent) : view(v), model(m), QObject(parent){
    //Connessione SIGNAL chiusura della View allo slot di onViewClosed che si occuperà nelle future
    //implementazioni di gestire la chiusura di una schermata(View/Ctrl/Model)
    connect(getView(),SIGNAL(viewClosed()),this,SLOT(onViewClosed()));
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
