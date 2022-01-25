#ifndef BARCHARTCTRL_H
#define BARCHARTCTRL_H

#include "ctrl/ctrl.h"
#include "view/barchartview.h"
#include "model/barchartmodel.h"

class BarChartCtrl : public Ctrl
{
    Q_OBJECT
public:
    explicit BarChartCtrl(BarChartView* v,BarChartModel* m, Ctrl* parent = nullptr) :
        Ctrl(v,m,parent){
        qDebug() << "meseA totali" << getModel()->getMeseATotali();
        qDebug() << "lsit materiali" << getModel()->getMaterialList();

        //Cliclo tutti i materiali e creo una lista con in ordine i suoi consumi in ordine di meseA
        for(const auto& materiale : getModel()->getMaterialList()){
            std::list<uint> consumiMensili;
            //ciclo le tutte le meseA e per ciascuna prendo il consumo del meseA e del materiale
            for(const auto& meseA : getModel()->getMeseATotali()){
                consumiMensili.push_back(getModel()->getDataMaterialiConsumi()[meseA][materiale]);
            }
            qDebug() << "lsita inserimenti consumi totale" << consumiMensili;
            //inserisco all'interno della view il materiale e i suoi consumi
            getView()->insertSetMateriale(materiale,consumiMensili);
        }

        //Applico alla view i dati al chart
        getView()->applySetsOnChart();

        //Inserisco alla view agli assi la lista con i mesiA e il max valore Y cioè consumoTotale
        getView()->applyAxis(getModel()->getMeseATotali(),20);//getModel()->getConsumoMax()

    }

    /**
     * @brief getView metodo virtuale che restituisce il campo view castato
     * al tipo corrente BarChartView
     * @return view
     */
    BarChartView* getView() const override{
        return static_cast<BarChartView*>(view);
    }
    /**
     * @brief getModel metodo virtuale che restituisce il campo model castato
     * al tipo corrente BarChartModel
     * @return
     */
    BarChartModel* getModel() const override{
        return static_cast<BarChartModel*>(model);
    }

    void showView() const override{
        view->show();
    }

public slots:
    /**
     * @brief onViewClosed Metodo virtuale che definisce il cosa fare alla chiusura della schermata
     * in questo caso NIENTE, distrugge solamente il costruttore
     */
    void onViewClosed() const override{
        qDebug() << "barChartView closed";
        delete this;
    }


};

#endif // BARCHARTCTRL_H
