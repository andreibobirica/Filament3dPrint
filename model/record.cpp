#include "record.h"

Record::Record(QString m, unsigned int d,unsigned int mU,const QDate& da):
    materiale(m), durata(d), matUsato(mU), data(da){}

const QString& Record::getMateriale() const{
    return materiale;
}

unsigned int Record::getDurata() const{
    return durata;
}

unsigned int Record::getMatUsato() const{
    return matUsato;
}

const QDate& Record::getData() const{
    return data;
}

/*
const QString& Record::toString() const{
    return QString("Materiale: "+getMateriale()+" | Durata: "+QString::number(getDurata())+" | MatUsato: "+QString::number(getMatUsato())+ " | Date: "+getData().toString());
}
*/
