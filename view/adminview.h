#ifndef ADMINVIEW_H
#define ADMINVIEW_H

#include "view/view.h"

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
#include <QComboBox>

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

    QPushButton* pieChartB;
    QPushButton* pieChartDetailB;
    QPushButton* lineChartB;
    QPushButton* barChartB;
    QPushButton* barChartOldB;


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
     * Viene poi emesso un segnale al controller per avvisarlo della chiusura della finestra.
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

    /**
     * @brief setViewTitle Metodo che setta il titolo alla view, aggiunge al titolo il prefisso "Progetto"
     * @param title titolo della view
     */
    void setViewTitle (const QString &title) override;

    /**
     * @brief createRecordTable Crea la QTableWidget su cui poi mostrare i dati.
     * @param headers Etichette da mostrare
     */
    void createRecordTable(const QStringList& headers) const;

    /**
     * @brief addItemRecordTable Metodo che aggiunge una nuova riga alla filamentTable, la riga rappresenta
     * un Record come dato.
     * Mostra ciascun dato con per ciascuno un input QT adeguato, e alla fine della riga l'ultima colonna
     * aggiunge un pulsante che serve ad eliminare la riga.
     * All'inizio si occupa di richiamare createAddRecordTable una riga più in basso, appunto per spostare la
     * riga di inserimento di un nuovo record.
     * successivamente mostra per ogni caso, per ogni colonna un QWidget adeguato.
     * Ad ogni QWidget ci assoccia anche delle connessioni lambda che seviranno a intercettare eventi di modifica
     * del dato e tramite dei segnali della View verranno reindirizzati al Controller insieme al nuovo dato e alla riga in questione.
     * Ci sono altri segnali associati cioè quello assocciato al ultimo pulsante Delete, che si occupa tramite
     * una connessione lambda di eliminare la riga in questione ed i suoi QWidget e le connessioni associate.
     * Ci sono poi altre connessioni iniziali solo per la prima colonna di MaterialW (Add/Remove/Modify) le quali
     * intercettano i cambiamenti che avvengono nella tabella di materialTable e adeguano il QComboBox modificando di conseguenza
     * le opzioni scheglibili.
     *
     * Un particolare occhio di attenzione va dato alle connessioni lambda le quali essendo tra oggetti nello heap
     * e con funzioni anonime possono generare facilmente Undefined Behavior se mal gestite.
     * In questo caso però ho preso cura di assocurarmi che che gli oggetti dda cui partono segnali o a cui arrivano slot
     * vengano distrutti (tramite il meccanismo di parentela) e le connessioni vengano disconnesse.
     * @param row Riga in cui fare la aggiuntaa
     * @param r Record da aggiungere
     * @param materialList lista di materiali tra cui scegliere per la cella di selezione materiale
     */
    void addItemRecordTable(unsigned int row,const Record& r,const QStringList& materialList);

    /**
     * @brief createAddRowRecordTable Crea una riga specifica di add, alla riga row, in cui appone uno spazione nuovo su cui
     * si potrà inserire i dettagli di un nuovo record.
     * Associa in fine al pulsante + creato anche una connessione per Segnale la quale Aggiornerà anche il Model.
     * @param row riga a cui aggiungere la riga di add
     */
    void createAddRowRecordTable(unsigned int row, const QStringList& materialList);

    /**
     * @brief createMaterialTable Crea la QTableWidget su cui mostrare i dati
     * @param headers Etichette da mostrare
     */
    void createMaterialTable(const QStringList& headers) const;
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
    void addItemMaterialTable(unsigned int row, const QString& m);


    /**
     * @brief modifyItemMaterialTable Metodo che modifica uno specifico Material
     * della materialTable
     * Infine viene emesso un segnale per aggiornare anche i QComboBox con la modifica
     * da fare al materiale
     * @param row
     * @param m
     */
    void modifyItemMaterialTable(unsigned int row, const QString& m);

    /**
     * @brief removeItemMaterialTable Metodo che elimina un item della record table
     * Viene emmesso il segnale materialTableRemovedChecked(row) per aggiornare
     * i QComboBox per il materiale della recordTable
     * @param row riga del Materiale da rimuovere
     */
    void removeItemMaterialTable(unsigned int row);

signals:
    //SIGNAL catturatti da un Controller, servono per aggiornare il Model con la modifica della RecordTable
    void recordTableRemoved(uint) const;
    void recordTableAdded(QString, uint, uint, QDate) const;
    void recordTableMaterialeMod(uint, QString) const;
    void recordTableDurataMod(uint, uint) const;
    void recordTableMatUsatoMod(uint, uint) const;
    void recordTableDataMod(uint, QDate) const;

    //SIGNAL catturati da un Controller, servono per aggiornare il Model con la modifica del materialTable
    void materialTableAdded(QString) const;
    void materialTableMaterialeMod(uint,QString) const;
    void materialTableRemoved(uint) const;

    //SIGNAL catturati dalla View, servono per aggiornare i QComboBox con la modifica del campo dato Materiale della RecordTable
    void materialTableAddedChecked(QString) const;
    void materialTableMaterialeModChecked(uint,QString) const;
    void materialTableRemovedChecked(uint) const;

    //SIGNAL catturati da un Controller, servono per eseguire delle azioni
    void newBPressed() const;
    void saveBPressed() const;
    void saveAsBPressed() const;
    void homeBPressed() const;
    void pieChartBPressed(bool) const;
    void lineChartBPressed() const;
    void barChartBPressed(bool) const;

public slots:

};

#endif // ADMINVIEW_H
