#include "barchartctrl.h"

BarChartCtrl::BarChartCtrl(BarChartView *v, BarChartModel *m, Ctrl *parent) :
    Ctrl(v,m,parent){
    //Cliclo tutti i materiali e creo una lista con in ordine i suoi consumi in ordine di meseA
    for(const auto& materiale : getModel()->getMaterialList()){
        std::list<uint> consumiMensili;
        //ciclo le tutte le meseA e per ciascuna prendo il consumo del meseA e del materiale
        for(const auto& meseA : getModel()->getMeseATotali()){
            consumiMensili.push_back(getModel()->getDataMaterialiConsumi()[meseA][materiale]);
        }
        //inserisco all'interno della view il materiale e i suoi consumi
        getView()->insertSetMateriale(materiale,consumiMensili);
    }

    //Applico alla view i dati al chart
    getView()->applySetsOnChart();

    //Inserisco alla view agli assi la lista con i mesiA e il max valore Y cioè consumoTotale
    getView()->applyAxis(getModel()->getMeseATotali(),getModel()->getConsumoMassimo());

}

BarChartView *BarChartCtrl::getView() const{
    return static_cast<BarChartView*>(view);
}

BarChartModel *BarChartCtrl::getModel() const{
    return static_cast<BarChartModel*>(model);
}

void BarChartCtrl::showView() const{
    view->showInformationDialog("Attenzione","Di seguito il grafico con i consumi totali.");
    view->show();
}

void BarChartCtrl::onViewClosed() const{
    delete this;
}
