#include "piechartctrl.h"

PieChartCtrl::PieChartCtrl(PieChartView* v, PieChartModel* m, Ctrl* parent) : Ctrl(v,m,parent){
    //Per ogni Materiale, se il suo utilizzo (occurence), è maggiore di zero, lo mostor nel grafico a torta
    for (const auto& kv : getModel()->getMaterialOccurrences()) {
        if(kv.second != 0)
        getView()->insertMaterial(kv.first,kv.second);
    }

    //Applico la grafica e le personalizzazioni della torta
    getView()->applyGraphics();
}

PieChartView *PieChartCtrl::getView() const{
    return static_cast<PieChartView*>(view);
}

PieChartModel *PieChartCtrl::getModel() const{
    return static_cast<PieChartModel*>(model);
}

void PieChartCtrl::onViewClosed() const{
    delete this;
}
