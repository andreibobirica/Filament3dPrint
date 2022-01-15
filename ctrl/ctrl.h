#ifndef CTRL_H
#define CTRL_H

#include <QWidget>


#include "view/view.h"

/**
 * @brief The Ctrl class
 * Classe Base polimorfa che fa da Controller collegato alla View su cui rappresentare il Model con dei dati
 */
class Ctrl : public QWidget
{
    Q_OBJECT
private:
    View* view;
public:
    /**
     * @brief Ctrl::Ctrl Costruttore
     * @param v View collegata al Controller
     */
    explicit Ctrl(View* v);
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
