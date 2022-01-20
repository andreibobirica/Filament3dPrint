#include "piechartmodel.h"

PieChartModel::PieChartModel(AdminModel *mAdmin){
    for(const QString& materiale : *mAdmin->getMaterialList()){
        unsigned int occurrences = 0;
        for(Record* r : mAdmin->getRecordList()){
            if(r->getMateriale() == materiale)
                occurrences++;
        }
        materialOccurrences.insert({materiale,occurrences});
    }
}

std::map<QString, unsigned int> PieChartModel::getMaterialOccurrences() const{
    return materialOccurrences;
}
