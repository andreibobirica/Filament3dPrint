#ifndef HOMEVIEW_H
#define HOMEVIEW_H

#include <QWidget>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QPushButton>
#include <QLabel>
#include <QPixmap>

#include "view/view.h"

/**
 * @brief The HomeView class
 * Classe derivata di View, è una View specializzata per la parte Home della applicazinoe
 */
class HomeView : public View
{
    Q_OBJECT
private:
    QPushButton* newPButton;
    QPushButton* openPButton;
    /**
     * @brief createButtonsLayout
     * Questo Metodo si occupa di realizare e predisporre il layout con i pulsanti del Home
     * @return Layout contenente i pulsanti con i pulsanti del menu Home
     * private perchè invocato solamente nel costruttore
     */
    QLayout* createButtonsLayout();
    /**
     * @brief createDescriptionLayout
     * Metodo che si occupa di realizzare e predisporre il layout con la parte descrittiva delLa Home
     * @return layout contenente la parte della descrizione della applicazione
     * private perchè invocato solamente nel costruttore
     */
    QLayout* createDescriptionLayout(const QString&,const QString&);
    /**
     * @brief connectViewSignals Metodo virtuale
     * Questo Metodo serve a connettere i SIGNAL degli elementi grafici della Homeview ai SIGNAL della
     * HomeView i quali dovranno comunicare con il Controller HomeCtrl
     */
    void connectViewSignals() const override;

protected:
    /**
     * @brief getMainLayout
     * @return Metodo getter che restituisce il MainLayout della View
     */
    QHBoxLayout* getMainLayout() const;

public:
    /**
     * @brief HomeView
     * Il Costruttore si occupa di Creare la View e creare i due layout laterali della app e mostrarli.
     * @param s Grandezza della finistra, la windowSize
     */
    explicit HomeView(QSize* s = new QSize(720,480),View* parent = nullptr);

signals:
    void newProject();
    void openProject();
public slots:
};

#endif // HOMEVIEW_H
