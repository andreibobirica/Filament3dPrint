#include "linechartctrl.h"

LineChartCtrl::LineChartCtrl(LineChartView *v, AdminModel *m, Ctrl *parent) : Ctrl(v,new AdminModel(*m),parent){
    for(auto r : getModel()->getRecordList()){
        getView()->insertMaterialData(r->getMateriale(),r->getDurata(),r->getMatUsato());
    }
    getView()->applyChartSeries();
}

LineChartView *LineChartCtrl::getView() const{
    return static_cast<LineChartView*>(view);
}

AdminModel *LineChartCtrl::getModel() const{
    return static_cast<AdminModel*>(model);
}

void LineChartCtrl::onViewClosed() const{
    qDebug() << "linechartView closed";
    delete this;
}
