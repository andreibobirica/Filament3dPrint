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


void View::showWarningDialog(const QString& mes,const QString& mesInfo){
    QMessageBox msgBox;
    msgBox.setText(mes);
    if(mesInfo != "")
        msgBox.setInformativeText(mesInfo);
    msgBox.setStandardButtons(QMessageBox::Ok);
    msgBox.setDefaultButton(QMessageBox::Ok);
    msgBox.exec();
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
