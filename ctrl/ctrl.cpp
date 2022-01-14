#include "ctrl/ctrl.h"

Ctrl::Ctrl(View* v) : view(v){}

View* Ctrl::getView() const {
    return view;
}

void Ctrl::showView() const{
    if(view->getWindowSize())
    view->show();
    else
    view->showFullScreen();
}

void Ctrl::hideView() const{
    view->hide();
}
