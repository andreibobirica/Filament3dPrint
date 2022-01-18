#ifndef ADMINCTRL_H
#define ADMINCTRL_H

#include <list>

#include "ctrl/ctrl.h"
#include "view/adminview.h"


/**
 * @brief The AdminCtrl class
 * AdminCtrl classe derivata da Ctrl ossia un Controller specializzato della schermata Admin della applicazione
 */
class AdminCtrl : public Ctrl
{
    Q_OBJECT
private:

    /**
     * @brief connectViewCtrlSignalsSlots Metodo virtuale
     * Questo Metodo serve a connettere i SIGNAL della AdminView ai Slot del AdminCtrl
     */
    void connectViewCtrlSignalsSlots() const override;

public:
    /**
     * @brief AdminCtrl
     * @param v View collegata al Controller
     * @param m Model collegato al Controller
     */
    AdminCtrl(AdminView* v, AdminModel* m = new AdminModel(), Ctrl* parent = nullptr);

    ~AdminCtrl() override{qDebug("AdminCtrl destructed");}

    /**
     * @brief getView Ritorna La View castata almeno al tipo AdminView
     * @return
     */
    AdminView* getView() const override;

    /**
     * @brief getModel Ritorna il Model castato almeno al tipo ModelView
     * @return
     */
    AdminModel* getModel() const override;

signals:

public slots:
     void onViewClosed() const override;
     void onRecordTableRemoved(unsigned int row);
     void onRecordTableAdded(const QString& m, unsigned int d, unsigned int mu, const QDate& da);
     void onRecordTableMaterialeMod(unsigned int row,const QString& m);
     void onRecordTableDurataMod(unsigned int row, unsigned int d);
     void onRecordTableMatUsatoMod(unsigned int row, unsigned int mu);
     void onRecordTableDataMod(unsigned int row, const QDate& da);
     void onMaterialTableAdded(const QString& m);
     void onMaterialTableMaterialeMod(unsigned int row,const QString& m);
     void onMaterialTableRemoved(unsigned int row);

     void onNewBPressed(){
         //domandare se chiudere
         //se si
         //Se non è stato impostato un padre non eseguire l'azione
         View* parentView = getView()->parent() ? static_cast<View*>(getView()->parent()) : nullptr;
         Ctrl* parentCtrl = parent() ? static_cast<Ctrl*>(parent()) : nullptr;

         AdminView* adminView = new AdminView(new QSize(720,480),parentView);
         AdminCtrl* adminCtrl = new AdminCtrl(adminView,new AdminModel(),parentCtrl);
         adminCtrl->showView();
         getView()->hide();
         delete this;
     }
     void onSaveBPressed(){}
     void onSaveAsBPressed(){}
     void onHomeBPressed(){
         //domandare se chiudere
         //se si
         if(getView()->parent()) static_cast<View*>(getView()->parent())->show();
         getView()->hide();
         delete this;
     }

};

#endif // ADMINCTRL_H
