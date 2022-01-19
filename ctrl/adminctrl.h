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
     * @brief getView Ritorna La View castata almeno al tipo corrente AdminView
     * @return
     */
    AdminView* getView() const override;

    /**
     * @brief getModel Ritorna il Model castato almeno al tipo corrente ModelView
     * @return
     */
    AdminModel* getModel() const override;

signals:

public slots:
     /**
      * @brief onViewClosed SLOT eseguito alla ricezione di SEGNALI di chiusura della View
      * In questo caso distrugger il suddetto controller, che di seguito distrugge la view e il model
      */
     void onViewClosed() const override;
     /**
      * @brief onRecordTableRemoved SLOT eseguito alla ricezione di SEGNALI dalla view per la rimozione
      * di un record dalla record table, questo slot modifica il modello aggiornandolo con il record da rimuovere
      * @param row indice del record da rimuovere dalla recordList
      */
     void onRecordTableRemoved(unsigned int row);

     /**
      * @brief onRecordTableAdded SLOT eseguito alla ricezione di SEGNALI dalla view per l'aggiunta di un record
      * viene quindi modificato il model aggiungendo un record alla recordList
      * @param m Materiale
      * @param d durata
      * @param mu materiale usato
      * @param da data di stampa
      */
     void onRecordTableAdded(const QString& m, unsigned int d, unsigned int mu, const QDate& da);

     /**
      * @brief onRecordTableMaterialeMod SLOT eseguito alla ricezione di SEGNALI dalla view
      * per la modifica del Materiale di uno specifico Record
      * @param row indice del record da modificare dalla recordList
      * @param m Materiale
      */
     void onRecordTableMaterialeMod(unsigned int row,const QString& m);

     /**
      * @brief onRecordTableDurataMod SLOT eseguito alla ricezione di SEGNALI dalla view per la
      * modifica della durata di uno specifico Record
      * @param row indice del record da modificare della recordList
      * @param d Durata
      */
     void onRecordTableDurataMod(unsigned int row, unsigned int d);

     /**
      * @brief onRecordTableMatUsatoMod SLOT eseguito alla ricezione di SEGNALI dalla view per la
      * modifica dela Mat Usato materiale usato di uno specifico record
      * @param row indice del record da modificare
      * @param mu materiale usato nella stampa
      */
     void onRecordTableMatUsatoMod(unsigned int row, unsigned int mu);

     /**
      * @brief onRecordTableDataMod SLOT eseguito alla ricezione di SEGNALI dalla view per la
      * modifica della data di uno specifico Record
      * @param row indice del record da modificare nella recordList
      * @param da Data
      */
     void onRecordTableDataMod(unsigned int row, const QDate& da);

     /**
      * @brief onMaterialTableAdded SLOT eseguito alla ricezione di SEGNALI dalla view per la
      * aggiunta di un materiale alla materialList
      * @param m Materiale
      */
     void onMaterialTableAdded(const QString& m);

     /**
      * @brief onMaterialTableMaterialeMod SLOT eseguito alla ricezione di SEGNALI dalla view
      * per la modifica di un materiale specifico dalla materialList
      * @param row indice del materiale da modificare dalla materialList
      * @param m Materiale
      */
     void onMaterialTableMaterialeMod(unsigned int row,const QString& m);

     /**
      * @brief onMaterialTableRemoved SLOT eseguito alla ricezione di SEGNALI dalla view
      * per la rimozione di uno specifico record dalla recordList
      * @param row indice del record da rimuovere
      */
     void onMaterialTableRemoved(unsigned int row);

     /**
      * @brief onNewBPressed SLOT eseguito alla ricezione di SEGNALI dalla view
      * Azione da eseguire per aprire un nuovo progetto
      */
     void onNewBPressed();

     /**
      * @brief onSaveBPressed SLOT eseguito alla ricezione di SEGNALI dalla view
      * azione eseguite per salvare il progetto
      */
     void onSaveBPressed()const;

     /**
      * @brief onSaveAsBPressed SLOT eseguito alla ricezione di SEGNALI dalla view
      * azione eseguita per salvare il progetto con un nome diverso
      */
     void onSaveAsBPressed()const;

     /**
      * @brief onHomeBPressed SLOT eseguito alla ricezione di SEGNALI dalla view
      * azione eseguita per tornare alla home
      */
     void onHomeBPressed();

};

#endif // ADMINCTRL_H
