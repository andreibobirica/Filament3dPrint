#include "jsonfilepicker.h"

QJsonDocument* JSONFilePicker::getJSONFileData(const QString& path){
    if(path.isNull()) return new QJsonDocument();

    QString fileData;
    QFile file;

    file.setFileName(path);
    file.open(QIODevice::ReadOnly | QIODevice::Text);
    fileData = file.readAll();
    file.close();

    QJsonDocument* jsonData = new QJsonDocument(QJsonDocument::fromJson(fileData.toLocal8Bit()));
    return jsonData;
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


