#include "adminmodel.h"

AdminModel::AdminModel(QJsonDocument *data){
    materialiList = JSONFilePicker::getMaterialList(data);
    recordList = JSONFilePicker::getRecords(data);
}

AdminModel::AdminModel(){
    materialiList = new QStringList();
}

QStringList* AdminModel::getMaterialList() const{ return materialiList;}

std::list<Record*> AdminModel::getRecordList() const{return recordList;}

void AdminModel::removeRecord(unsigned int row){
    std::list<Record*>::iterator it= recordList.begin();
    std::advance(it,row);
    recordList.erase(it);
}

Record* AdminModel::getRecord(unsigned int row){
    std::list<Record*>::iterator it= recordList.begin();
    std::advance(it,row);
    return *it;
}

void AdminModel::addRecord(Record *r){
    recordList.push_back(r);
}

unsigned int AdminModel::getRecordListSize(){return recordList.size();}

void AdminModel::addMaterial(const QString &m){
    materialiList->push_back(m);
}

void AdminModel::setMaterial(unsigned int row, const QString &m){
    materialiList->replace(row,m);
}

void AdminModel::removeMaterial(unsigned int row){
    materialiList->removeAt(row);
}
