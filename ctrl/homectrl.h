#ifndef HOMECTRL_H
#define HOMECTRL_H


#include "ctrl/ctrl.h"

#include <QFileDialog>
#include <QStringList>
#include <QJsonDocument>

#include "view/homeview.h"
#include "view/adminview.h"
#include "ctrl/adminctrl.h"
#include "model/adminmodel.h"
#include "ctrl/jsonfilepicker.h"

/**
 * @brief The HomeCtrl class
 * Classe Derivata da Ctrl, è il Controller specifico per la View HomeView
 * Serve a controllare tutto quello che riguarda la schermata Home della App
 */
class HomeCtrl : public Ctrl
{
    Q_OBJECT
private:

    /**
     * @brief connectViewCtrlSignalsSlots Metodo overloading
     * Questo Metodo serve a connettere i SIGNAL della AdminView ai Slot del AdminCtrl
     */
    void connectViewCtrlSignalsSlots() const;

public:
    /**
     * @brief HomeCtrl
     * @param v HomeView collegata al Controller
     * @param parent Controller Padre della schermata che ha invocato la Home, potrebbero esserci
     * in future implementazioni altre schermate prima della Home potrebbero esserci
     */
    explicit HomeCtrl(HomeView* v, Ctrl* parent = nullptr);

    /**
     * @brief getView
     * Metodo virtuale che restituisce la View del controller castata al tipo corretto
     * @return VIEW del Controller interpretata come HomeView
     */
    HomeView* getView() const override;

    Model* getModel() const override{
        //Non Ha un modello
        return nullptr;
    }

signals:

public slots:
    /**
     * @brief onNewProject SLOT eseguito alla ricezione di SEGNALI di apertura di un nuovo progetto
     */
    void onNewProject() const;
    /**
     * @brief onOpenProject SLOT eseguito alla ricezione di SEGNALI di apertura di un progetto esistente
     */
    void onOpenProject() const;
    /**
     * @brief onViewClosed SLOT eseguito alla ricezione di SEGNALI di chiusura della view
     * Le azioni che esegue sono la distruzione del suddetto Controller, successivamente con la distruzione
     * verranno distrutte anche la View (al di là se è visibile o no) e il Model
     */
    void onViewClosed() const override;
};

#endif // HOMECTRL_H
