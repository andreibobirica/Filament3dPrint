#include "ctrl/adminctrl.h"

AdminCtrl::AdminCtrl(View* v, Model* m, Ctrl* parent) : Ctrl(v,m,parent){
    //Collego i SIGNAL della View Ai SLOT del Controller
    connectViewCtrlSignalsSlots();
    //Creao la Record Table
    qDebug() << getModel()->getRecordList().size()+1;
    getView()->createRecordTable(0,5,{ "Materiale", "Durata", "Consumo", "Data",""});

    //Creo Prima Row Pulsante Add
    getView()->createAddRowRecordTable(0);

    //Popolo La RecordTable con i Record presi da Model
    unsigned int id = 0;
    for (Record* r : getModel()->getRecordList()) {
        getView()->addItemRecordTable(id++,r);
    }
}

AdminView* AdminCtrl::getView() const {
    return static_cast<AdminView*>(Ctrl::getView());
}

AdminModel* AdminCtrl::getModel() const {
    return static_cast<AdminModel*>(Ctrl::getModel());
}



void AdminCtrl::connectViewCtrlSignalsSlots() const{
    connect(getView(),SIGNAL(recordTableRemoved(uint)),this,SLOT(onRecordTableRemoved(uint)));
    connect(getView(),SIGNAL(recordTableAdded(QString,uint,uint,QDate)),this,SLOT(onRecordTableAdded(QString,uint,uint,QDate)));
    connect(getView(),SIGNAL(recordTableMaterialeMod(uint,QString)),this,SLOT(onRecordTableMaterialeMod(uint,QString)));
    connect(getView(),SIGNAL(recordTableDurataMod(uint,uint)),this,SLOT(onRecordTableDurataMod(uint,uint)));
    connect(getView(),SIGNAL(recordTableMatUsatoMod(uint,uint)),this,SLOT(onRecordTableMatUsatoMod(uint,uint)));
    connect(getView(),SIGNAL(recordTableDataMod(uint,QDate)),this,SLOT(onRecordTableDataMod(uint,QDate)));
}

void AdminCtrl::onViewClosed() const {
    delete this;
}

void AdminCtrl::onRecordTableRemoved(unsigned int row){
    getModel()->removeRecord(row);
}

void AdminCtrl::onRecordTableAdded(const QString & m, unsigned int d, unsigned int mu, const QDate& da){
    Record* r = new Record(m,d,mu,da);
    getModel()->addRecord(r);
    getView()->addItemRecordTable(getModel()->getRecordListSize()-1,r);
}

void AdminCtrl::onRecordTableMaterialeMod(unsigned int row, const QString& m){
    getModel()->getRecord(row)->setMateriale(m);
    qDebug() << getModel()->getRecord(row)->toString();
}

void AdminCtrl::onRecordTableDurataMod(unsigned int row, unsigned int d){
    getModel()->getRecord(row)->setDurata(d);
}

void AdminCtrl::onRecordTableMatUsatoMod(unsigned int row, unsigned int mu){
    getModel()->getRecord(row)->setMatUsato(mu);
}

void AdminCtrl::onRecordTableDataMod(unsigned int row, const QDate& da){
    getModel()->getRecord(row)->setData(da);
}
