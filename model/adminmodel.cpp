#include "adminmodel.h"

AdminModel::AdminModel(QJsonDocument *data, QString* path){
    materialiList = JSONFilePicker::getMaterialList(data);
    recordList = JSONFilePicker::getRecords(data);
    filepath = path;
}

AdminModel::AdminModel(){
    materialiList = new QStringList();
    filepath = new QString();
}

AdminModel::AdminModel(const AdminModel &m){
    filepath = new QString(*m.filepath);
    materialiList = new QStringList(*m.materialiList);
    for(const auto& r : m.recordList)
        recordList.push_back(new Record(*r));
}

AdminModel::~AdminModel(){
    delete filepath; delete materialiList;
    for(auto r : recordList)
        delete r;
}

QStringList* AdminModel::getMaterialList() const{ return materialiList;}

std::list<Record*> AdminModel::getRecordList() const{return recordList;}

void AdminModel::removeRecord(unsigned int row){
    std::list<Record*>::iterator it= recordList.begin();
    std::advance(it,row);
    recordList.erase(it);
}

Record* AdminModel::getRecord(unsigned int row) const{
    std::list<Record*>::const_iterator it= recordList.begin();
    std::advance(it,row);
    return *it;
}

const QString &AdminModel::getMaterial(unsigned int row) const{
    return materialiList->at(row);
}

const QJsonDocument &AdminModel::toQJSonDocument() const{
    QJsonDocument* modelJson = new QJsonDocument();
    QJsonObject mainObj;

    QJsonArray recordsArray;
    for(Record* r : recordList){
        QJsonObject recObj;
        recObj.insert(QString::fromStdString("materiale"),r->getMateriale());
        recObj.insert(QString::fromStdString("durata"),QJsonValue((int)r->getDurata()));
        recObj.insert(QString::fromStdString("matUsato"),QJsonValue((int)r->getMatUsato()));
        recObj.insert(QString::fromStdString("data"),r->getData().toString("dd/MM/yyyy"));
        recordsArray.push_back(recObj);
    }
    mainObj.insert(QString::fromStdString("materiali"),QJsonArray::fromStringList(*materialiList));
    mainObj.insert(QString::fromStdString("records"),recordsArray);
    modelJson->setObject(mainObj);

    return *modelJson;
}

void AdminModel::setFilePath(const QString &fname){
    *filepath = fname;
}

void AdminModel::addRecord(Record *r){
    recordList.push_back(r);
}

unsigned int AdminModel::getRecordListSize() const{return recordList.size();}

void AdminModel::addMaterial(const QString &m){
    materialiList->push_back(m);
}

void AdminModel::setMaterial(unsigned int row, const QString &m){
    materialiList->replace(row,m);
}

void AdminModel::removeMaterial(unsigned int row){
    materialiList->removeAt(row);
}

const QString& AdminModel::getFilePath() const{return *filepath;}
