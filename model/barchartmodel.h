#ifndef BARCHARTMODEL_H
#define BARCHARTMODEL_H

#include "model/model.h"

#include <map>
#include <list>
#include <QtAlgorithms>
#include <QLocale>

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
    //ConsumoMassimo trovato
    uint consumoMassimo = 0;

    /**
     * @brief insertMeseATotali Metodo privato ricorsivo
     * Date due date first e last prende tutti i mesi intermedi e li pusha nella lista
     * meseATotali in ordine.
     * Caso base, si è arrivati all'ultima data ed esce dal metodo
     * Caso ricorsivo, la data attuale è minore della successiva data quindi continua
     * richiamando insertMeseATotali(first.addMonths(1),last,meseATotali)
     * @param first data da cui cominciaer
     * @param last data a cui finire
     * @param meseATotali lista dei meseA su cui aggiungere
     */
    void insertMeseATotali(const QDate& first, const QDate& last, QStringList* meseATotali) const;
public:
    /**
     * @brief BarChartModel Costruttore del BarChart che usa un Admin Model per
     * costruire un modello di dati che servirà al bar CHart
     * @param am Admin Model
     */
    explicit BarChartModel(AdminModel* am);

    /**
     * @brief getMaterialList Metodo getter
     * @return  lita materiali
     */
    const QStringList& getMaterialList() const;

    /**
     * @brief getDataMaterialiConsumi metodo getter
     * @return mappa che rappresenta per ogni meseA una mappa con per ogni materiale il suo consumo totale
     */
    std::map<QString,std::map<QString,uint>> getDataMaterialiConsumi() const;

    /**
     * @brief getMeseATotali metodo getter
     * @return lista di tutti i meseA utilizzati
     */
    const QStringList& getMeseATotali() const;

    /**
     * @brief getConsumoMassimo metodo getter
     * @return consumo massimo utilizzato all'interno di questo modello
     */
    uint getConsumoMassimo() const;
};

#endif // BARCHARTMODEL_H
