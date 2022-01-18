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
#include <QDateEdit>
#include <QSpinBox>
#include <QTextEdit>

#include "view/view.h"
#include "model/adminmodel.h"

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
    QTableWidget* filamentTable;

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

    ~AdminView() override{qDebug("AdminView destructor");}

    /**
     * @brief addItemRecordTable Metodo che aggiunge ad una QTableWidget,
     * in particolare alla filamentTable, aggiunge un Modello di dato specifico cioè un Record.
     * Questa aggiunta avviene ad una riga precisa della tabllea row.
     * Attenzione che si occupa anche di associare un pulsante ad ogni Riga.
     * Attenzione che si occupa anche di associare nelle connessioni di signali ai pulsanti.
     * @param row Riga in cui fare la aggiunta
     * @param r Record da aggiungere
     */
    void addItemRecordTable(unsigned int row, Record *r);

    /**
     * @brief createRecordTable Crea la QTableWidget su cui poi mostrare i dati.
     * @param row righe della tabella
     * @param column colonne della tabella
     * @param headers Etichette da mostrare
     */
    void createRecordTable(unsigned int row, unsigned int column, QStringList headers) const;

    /**
     * @brief createAddRowRecordTable Crea una riga specifica di add, alla riga row, in cui appone uno spazione nuovo su cui
     * si potrà inserire i dettagli di un nuovo record.
     * Associa in fine al pulsante + creato anche una connessione per Segnale la quale Aggiornerà anche il Model.
     * @param row riga a cui aggiungere la riga di add
     */
    void createAddRowRecordTable(unsigned int row);

signals:
    void recordTableRemoved(uint);
    void recordTableAdded(QString, uint, uint, QDate);

public slots:

};

#endif // ADMINVIEW_H
