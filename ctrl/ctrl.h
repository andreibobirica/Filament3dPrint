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
private:
    View* view;
    Model* model;

    /**
     * @brief connectViewCtrlSignalsSlots Metodo virtuale puro
     * Questo Metodo serve a connettere i SIGNAL che la View invia ai SLOT del Controller
     * La sua futura implementazione necessita di collegare nello specifico SIGNAL E SLOT specifici
     *
     */
    virtual void connectViewCtrlSignalsSlots() const = 0;

public:
    /**
     * @brief Ctrl::Ctrl Costruttore
     * @param v View collegata al Controller
     */
    explicit Ctrl(View* v, Model* m, Ctrl* parent);

    /**
     * @brief Ctrl::getView
     * @return View collegata al Controller
     */
    virtual View* getView() const;

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

};

#endif // CTRL_H
