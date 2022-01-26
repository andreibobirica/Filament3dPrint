#ifndef CTRL_H
#define CTRL_H

#include <QObject>

#include "view/view.h"
#include "model/model.h"

/**
 * @brief The Ctrl class
 * Classe Base polimorfa che fa da Controller collegato alla View su cui rappresentare il Model con dei dati
 */
class Ctrl : public QObject
{
    Q_OBJECT
protected:
    View* view;
    Model* model;

private:
    /**
     * @brief connectViewCtrlSignalsSlots Metodo overloading
     * Questo Metodo serve a connettere i SIGNAL della AdminView ai Slot del AdminCtrl
     */
    void connectViewCtrlSignalsSlots() const;

public:
    /**
     * @brief Ctrl::Ctrl Costruttore del Controller di una schermata
     * @param v View collegata al Controller
     * @param m Model modello dei dati da rappresentare nella schermata
     * @param parent Padre del Controller, è il controller della schermata che ha creato la suddettas
     */
    explicit Ctrl(View* v, Model* m, Ctrl* parent = nullptr);

    virtual ~Ctrl() {
        setParent(nullptr);
        qDebug("Ctrl destructed");
        for(auto child : children())
            delete child;
        delete view; delete model;
    }

    /**
     * @brief Ctrl::getView
     * @return View collegata al Controller
     */
    virtual View* getView() const;

    /**
     * @brief getModel Metodo getter
     * @return Model Collegato al Controller
     */
    virtual Model* getModel() const;

    /**
     * @brief Ctrl::showView Metodo che rende visibile la View collegata al Controller
     * Se la View ha un WindowsSize, la mostra secondo quelle dimensioni
     * Se la View non ha un WindowSize la mostra a schermo intero
     */
    virtual void showView() const;
    /**
     * @brief Ctrl::hideView Metodo per nascondere la View
     */
    virtual void hideView() const;

signals:

public slots:
    /**
     * @brief onViewClosed SLOT eseguito in ricezione di SIGNAL di chiusura della View
     * è dichiarata come virtuale pura per implementare questa interfaccia obbligatoria per le future
     * classi derivate, cioè i Controller specifici di ogni schermata
     */
    virtual void onViewClosed() const = 0;

};

#endif // CTRL_H
