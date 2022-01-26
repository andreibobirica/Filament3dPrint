#ifndef HOMEVIEW_H
#define HOMEVIEW_H

#include "view/view.h"

#include <QWidget>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QPushButton>
#include <QLabel>
#include <QPixmap>
#include <QCloseEvent>
#include <QGroupBox>

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
     * @param description descrizione da inserire all'interno del layout
     * @param imgPath path della immagine da includere nel layout
     * @return layout contenente la parte della descrizione della applicazione
     * private perchè invocato solamente nel costruttore
     */
    QLayout* createDescriptionLayout(const QString& description, const QString& imgPath);
    /**
     * @brief connectViewSignals Metodo virtuale
     * Questo Metodo serve a connettere i SIGNAL degli elementi grafici della Homeview ai SIGNAL della
     * HomeView i quali dovranno comunicare con il Controller HomeCtrl
     */
    void connectViewSignals() const override;

protected:
    /**
     * @brief closeEvent Overriding del metodo closeEvent implementato da QWidget
     * Tramite questo Overriding si cerca di modificare il da farsi nel evento di chiusura della window con la X.
     * In particolare questo metodo chiede una conferma al utente prima di chiudere.
     * Viene poi emesso un segnale per avvisare il controller della chiusura
     * @param event Evento di chiusura della scermata window
     */
    void closeEvent(QCloseEvent *event) override;
public:
    /**
     * @brief HomeView
     * Il Costruttore si occupa di Creare la View e creare i due layout laterali della app e mostrarli.
     * @param s Grandezza della finistra, la windowSize
     */
    explicit HomeView(const QSize& s = QSize(),View* parent = nullptr);

signals:
    void newProject() const;
    void openProject() const;

public slots:

};

#endif // HOMEVIEW_H
