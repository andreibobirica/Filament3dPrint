#include "jsonfilepicker.h"

QJsonDocument* JSONFilePicker::getJSONFileData(const QString& path){
    if(path.isNull()) return new QJsonDocument();

    QString fileData;
    QFile file;

    file.setFileName(path);
    file.open(QIODevice::ReadOnly | QIODevice::Text);
    fileData = file.readAll();
    file.close();

    //Controllo validità documento
    QJsonDocument* doc = new QJsonDocument(QJsonDocument::fromJson(fileData.toLocal8Bit()));
    QJsonObject dataObj = doc->object();
    if(!dataObj.contains("records") || !dataObj.contains("materiali")){
        delete doc;
        return new QJsonDocument();
    }
    return doc;
}

QString JSONFilePicker::selectJSONFileDialog(){
    QFileDialog dialog;
    dialog.setFileMode(QFileDialog::ExistingFile);
    dialog.setNameFilter("JSON File (*.json)");
    QString fileName;
    if (dialog.exec())
        fileName = dialog.selectedFiles().at(0);
    return fileName;
}

QStringList* JSONFilePicker::getMaterialList(QJsonDocument* data){
    QStringList* materialiList = new QStringList;
    QJsonObject dataObj = data->object();
    QJsonArray materialiArray = dataObj["materiali"].toArray();
    for(const QJsonValue& value : materialiArray) {
        materialiList->append(value.toString());
    }
    return materialiList;
}

std::list<Record*> JSONFilePicker::getRecords(QJsonDocument* data){
    std::list<Record*> ret;
    QJsonObject dataObj = data->object();
    QJsonArray records = dataObj["records"].toArray();
    for(const QJsonValue& record : records){
        Record* r = new Record(
                record.toObject().value("materiale").toString(),
                record.toObject().value("durata").toInt(),
                record.toObject().value("matUsato").toInt(),
                QDate::fromString(record.toObject().value("data").toString(),"dd/MM/yyyy"));
        ret.push_back(r);
    }
    return ret;
}

bool JSONFilePicker::saveAdminModel(const QJsonDocument& doc, const QString& path){
    if(path.isNull() || path.isEmpty()) return false;
    QFile file(path);
    if(file.open(QFile::WriteOnly | QFile::Text | QFile::Truncate)){
        file.write(doc.toJson());
        file.close();
        return true;
    }
    return false;
}


