#ifndef ADMINVIEW_H
#define ADMINVIEW_H

#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QPushButton>
#include <QLabel>
#include <QPixmap>
#include <QGroupBox>
#include <QLineEdit>
#include <QTableWidget>
#include <QScrollArea>
#include <QCloseEvent>
#include <QMessageBox>

#include "view/view.h"

/**
 * @brief The AdminView class
 * Classe derivata da View
 * View specializzata nella Parte Admin della applicazione, ossia la parte di amministrazione dei dati da elaborare
 */
class AdminView : public View
{
    Q_OBJECT
private:
    QGridLayout* mainLayout;

    /**
     * @brief connectViewSignals Metodo virtuale
     * Questo Metodo serve a connettere i SIGNAL degli elementi grafici della AdminView ai SIGNAL della
     * AdminView i quali dovranno comunicare con il Controller AdminCtrl
     */
    void connectViewSignals() const override;

protected:
    /**
     * @brief closeEvent Overriding del metodo closeEvent implementato da QWidget
     * Tramite questo Overriding si cerca di modificare il da farsi nel evento di chiusura della window con la X.
     * In particolare questo metodo chiede una conferma al utente prima di chiudere.
     * Successivamente una volta effettuata la chiusura, Mostra il Parent, cioè la schermata HomeView.
     * In fine si occupa della distruzione totale della schermata Admin(VIEW/MODEL/CTRL)
     * @param event Evento di chiusura della scermata window
     */
    void closeEvent(QCloseEvent* event) override;

public:
    /**
     * @brief AdminView
     * Costruttore della Admin View
     * @param s windowSize, grandezza della finestra della View
     */
    explicit AdminView(QSize* s = nullptr, View* parent = nullptr);


signals:

public slots:
};

#endif // ADMINVIEW_H
