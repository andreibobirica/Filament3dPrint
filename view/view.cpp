#include "view/view.h"

View::View(QSize* s,View* parent) : windowSize(s), QWidget(parent,Qt::Window){
    //Resizing della windows
    if(windowSize)
    applyWindowSize(windowSize);
}

void View::applyWindowSize(QSize* s){
    resize(*s);
}

void View::setWindowSize(QSize* s){
    windowSize = s;
}

QSize* View::getWindowSize() const{
    return windowSize;
}
