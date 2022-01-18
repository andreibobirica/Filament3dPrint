#include "view/view.h"

#include <QDebug>

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


void View::showInformationDialog(const QString& title, const QString& mesInfo){
    QMessageBox::information(this,title,mesInfo,QMessageBox::Ok);
}

void View::showCriticalDialog(const QString& title, const QString& mesInfo){
    QMessageBox::critical(this,title,mesInfo,QMessageBox::Ok);
}

void View::showWarningDialog(const QString& title, const QString& mesInfo){
    QMessageBox::warning(this,title,mesInfo,QMessageBox::Ok);
}


bool View::showQuestionDialog(unsigned int paramNum, const QString& title,const QString& info){
    QMessageBox::StandardButton resBtn = QMessageBox::Yes;
    switch (paramNum)
    {
        case 2:
            resBtn = QMessageBox::question( this,title,info,QMessageBox::No | QMessageBox::Yes | QMessageBox::Yes);
        break;
        default:
            resBtn = QMessageBox::question( this,title,info,QMessageBox::Cancel | QMessageBox::No | QMessageBox::Yes | QMessageBox::Yes);
        break;
    }
    return (resBtn == QMessageBox::Yes);
}
