#ifndef PIECHARTMODEL_H
#define PIECHARTMODEL_H

#include "model/model.h"
#include "model/adminmodel.h"

/**
 * @brief The PieChartModel class Modello che serve a rappresentare i dati da mostrare nella
 * schermata PieChart
 */
class PieChartModel : public Model
{
private:
    std::map<QString,unsigned int> materialOccurrences;
public:
    /**
     * @brief PieChartModel Costruttore che a partire da un AdminModel viene usato per costruire
     * un PieChartModel, il sudetto modello elabora le info del AdminModel
     * per creareuna mappa materialOccurences con:
     * Per ogni materiale il suo numero di utilizzi
     * @param mAdmin
     */
    explicit PieChartModel(AdminModel* mAdmin);

    /**
     * @brief getMaterialOccurrences Metodo getter che serve a ritornare
     * @return materialOccrences mappa con per ogni materiale il numero di utilizzi
     */
    std::map<QString,unsigned int> getMaterialOccurrences() const;
};

#endif // PIECHARTMODEL_H
