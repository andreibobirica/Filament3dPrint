#ifndef BARCHARTMODEL_H
#define BARCHARTMODEL_H

#include <map>
#include <list>
#include <QtAlgorithms>

#include "model/model.h"
#include "model/adminmodel.h"

class BarChartModel : public Model
{
private:
    //creo la struttura dati std::map<QString,std::map<QString,uint>>
    //Ad ogni meseA ho una mappa che rapresenta un Materiale ed il suo consumo totale per quel meseA
    //un meseA è un meseAnno "Gennaio 2022"
    std::map<QString,std::map<QString,uint>> dataMaterialiConsumi;
    //Lista meseA con tutti i mesi trattati dal modello in ordine
    QStringList meseATotali;
    //Lista con tutti i materiali
    QStringList materialList;
    /**
     * @brief insertMeseATotali Metodo privato ricorsivo
     * Date due date first e last prende tutti i mesi intermedi e li pusha nella lista
     * meseATotali in ordine.
     * Caso base, si è arrivati all'ultima data ed esce dal metodo
     * Caso ricorsivo, la data attuale è minore della successiva data quindi continua
     * richiamando insertMeseATotali(first.addMonths(1),last,meseATotali)
     * @param first
     * @param last
     * @param meseATotali
     */
    void insertMeseATotali(const QDate& first, const QDate& last, QStringList* meseATotali) const{
        QString meseA = QLocale(QLocale::Italian).toString(first,"MMMM yyyy");
        meseATotali->push_back(meseA);
        if(first < last)
            insertMeseATotali(first.addMonths(1),last,meseATotali);
    }
public:
    explicit BarChartModel(AdminModel* am){

        //Copio la lista dei materiali
        materialList = *(am->getMaterialList());

        //Ordino la recordList in base alla Data
        std::list<Record*> recordListOrdinata = am->getRecordList();
        recordListOrdinata.sort([](Record* lhs,Record* rhs) {return lhs->getData() < rhs->getData();});

        //Inserisco all'interno della struttura dati dataMaterialiConsumi i record e i loro dati
        for(Record* r : recordListOrdinata){
           const QString& meseA = QLocale(QLocale::Italian).toString(r->getData(),"MMMM yyyy");
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
                dataMaterialiConsumi[dmc.first] = matConsumo;
            }
        }
    }

    const QStringList& getMaterialList(){
        return materialList;
    }

    std::map<QString,std::map<QString,uint>> getDataMaterialiConsumi(){
        return dataMaterialiConsumi;
    }

    const QStringList& getMeseATotali(){
        return meseATotali;
    }
};

#endif // BARCHARTMODEL_H
