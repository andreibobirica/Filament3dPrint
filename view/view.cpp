#include "view.h"

View::View(QSize* s) : windowSize(s){
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
