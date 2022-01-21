#ifndef LINECHARTCTRL_H
#define LINECHARTCTRL_H

#include "view/linechartview.h"
#include "ctrl/ctrl.h"
#include "model/adminmodel.h"

class LineChartCtrl : public Ctrl
{
    Q_OBJECT
public:
    LineChartCtrl(LineChartView* v,AdminModel* m, Ctrl* parent = nullptr) : Ctrl(v,new AdminModel(*m),parent){
        for(auto r : getModel()->getRecordList()){
            getView()->insertMaterialRecord(r->getMateriale(),r->getDurata(),r->getMatUsato());
        }
        getView()->applyChartSeries();
    }

    LineChartView* getView() const{
        return static_cast<LineChartView*>(view);
    }

    AdminModel* getModel() const{
        return static_cast<AdminModel*>(model);
    }

    ~LineChartCtrl() override{
        qDebug() << "LineChartCtrl Destructed";
    }

public slots:
    /**
     * @brief onViewClosed Metodo virtuale che definisce il cosa fare alla chiusura della schermata
     * in questo caso NIENTE, distrugge solamente il costruttore
     */
    void onViewClosed() const override{
        qDebug() << "linechartView closed";
        delete this;
    }
};

#endif // LINECHARTCTRL_H
