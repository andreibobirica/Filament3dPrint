#include "barchartmodel.h"

void BarChartModel::insertMeseATotali(const QDate &first, const QDate &last, QStringList *meseATotali) const{
    QString meseA = QLocale(QLocale::Italian).toString(first,"MMMM yy");
    meseATotali->push_back(meseA);
    if(first < last)
        insertMeseATotali(first.addMonths(1),last,meseATotali);
}

BarChartModel::BarChartModel(AdminModel *am){

    //Copio la lista dei materiali
    materialList = *(am->getMaterialList());

    //Ordino la recordList in base alla Data
    std::list<Record*> recordListOrdinata = am->getRecordList();
    recordListOrdinata.sort([](Record* lhs,Record* rhs) {return lhs->getData() < rhs->getData();});

    //Inserisco all'interno della struttura dati dataMaterialiConsumi i record e i loro dati
    for(Record* r : recordListOrdinata){
        QString meseA = QLocale(QLocale::Italian).toString(r->getData(),"MMMM yy");
        dataMaterialiConsumi[meseA][r->getMateriale()] += r->getMatUsato();
    }

    //Nella struttura dati dataMaterialiConsumi mancano delle date
    //se il primo meseA è gennaio 2021 e l'ultimo è marzo 2021
    //manca il mese di febbraio 2021
    QDate first = recordListOrdinata.front()->getData();
    QDate last = recordListOrdinata.back()->getData();
    insertMeseATotali(first,last,&meseATotali);
    for(const auto& meseA: meseATotali){
        if(dataMaterialiConsumi.find(meseA) == dataMaterialiConsumi.end())
            dataMaterialiConsumi[meseA] = std::map<QString,uint>();
    }

    //Nella struttura dati dataMaterialiConsumi mancano dei materiali
    //mancano i materiali che non sono stati usati in certi mesi.
    //Per ogni meseA controllo se esistono datti i materiali e se non esistono
    //li inserisco con consumo totale 0;
    for (const auto& dmc : dataMaterialiConsumi) {
        //Cerco se esistono tutti i materiali
        std::map<QString,uint> matConsumo = dmc.second;
        for(const auto& materiale : *am->getMaterialList()){
            if(!(matConsumo.find(materiale) != matConsumo.end()))
                matConsumo[materiale] = 0;
            else//Se il cosumo totale esiste lo analizzo per memorizzare il massimo
                consumoMassimo = matConsumo[materiale] > consumoMassimo ? matConsumo[materiale] : consumoMassimo;
            //risalvo il materiale
            dataMaterialiConsumi[dmc.first] = matConsumo;
        }
    }
}

const QStringList &BarChartModel::getMaterialList() const{
    return materialList;
}

std::map<QString, std::map<QString, uint> > BarChartModel::getDataMaterialiConsumi() const{
    return dataMaterialiConsumi;
}

const QStringList &BarChartModel::getMeseATotali() const{
    return meseATotali;
}

uint BarChartModel::getConsumoMassimo() const{
    return consumoMassimo;
}
