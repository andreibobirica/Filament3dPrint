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
    QTableWidget* materialTable;
    QPushButton* homeB;
    QPushButton* newB;
    QPushButton* saveB;
    QPushButton* saveAsB;


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
    explicit AdminView(const QSize& s = QSize(), View* parent = nullptr);

    ~AdminView() override{qDebug("AdminView destructor");}

    /**
     * @brief addItemRecordTable Metodo che aggiunge ad una QTableWidget,
     * in particolare alla filamentTable, aggiunge un Modello di dato specifico cioè un Record.
     * Questa aggiunta avviene ad una riga precisa della tabllea row.
     * Attenzione che si occupa anche di associare un pulsante ad ogni Riga.
     * Attenzione che si occupa anche di associare nelle connessioni di signali ai pulsanti e alla modifica dei campi
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

    /**
     * @brief createMaterialTable Crea la QTableWidget su cui mostrare i dati
     * @param row numero di righe che dovrà avere
     * @param column numero di colonne che dovrà avere
     * @param headers Etichette da mostrare
     */
    void createMaterialTable(unsigned int row, unsigned int column, QStringList headers) const;
    /**
     * @brief createAddRowMaterialTable Metodo che si occupa di creare la riga di inserimento dei materiali, in questa
     * riga si potranno inserire i dettagli di un nuovo materiale
     * @param row riga alla cui creare
     */
    void createAddRowMaterialTable(unsigned int row);
    /**
     * @brief addItemMaterialTable Metodo che aggiunge ad una QTableWidget,
     * in particolare alla materialTable, aggiunge un Modello di dato specifico cioè un QString preso dal Model.
     * Questa aggiunta avviene ad una riga precisa della tabella row.
     * Attenzione che si occupa anche di associare un pulsante ad ogni Riga.
     * Attenzione che si occupa anche di associare nelle connessioni di signali ai pulsanti e alla modifica dei campi
     * @param row
     * @param m
     */
    void addItemMaterialTable(unsigned int row, const QString &m);

    /**
     * @brief setViewTitle Metodo che setta il titolo alla view, aggiunge al titolo il prefisso "Progetto"
     * @param title titolo della view
     */
    void setViewTitle (const QString &title) override;

signals:
    void recordTableRemoved(uint);
    void recordTableAdded(QString, uint, uint, QDate);
    void recordTableMaterialeMod(uint, QString);
    void recordTableDurataMod(uint, uint);
    void recordTableMatUsatoMod(uint, uint);
    void recordTableDataMod(uint, QDate);
    void materialTableAdded(QString);
    void materialTableMaterialeMod(uint,QString);
    void materialTableRemoved(uint);

    void newBPressed();
    void saveBPressed();
    void saveAsBPressed();
    void homeBPressed();

public slots:

};

#endif // ADMINVIEW_H
