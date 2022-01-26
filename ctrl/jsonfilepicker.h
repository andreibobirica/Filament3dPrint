#ifndef JSONFILEPICKER_H
#define JSONFILEPICKER_H

#include <QFile>
#include <QFileDialog>
#include <QJsonArray>
#include <QJsonDocument>
#include <QJsonObject>
#include <QMessageBox>

#include "model/record.h"
#include "model/adminmodel.h"

/**
 * @brief The JSONFilePicker class Classe che si occupa di lettura di File, Memorizzazione, Interpretazione Json
 * Estente QObject perchè ha componenti grafici che necessitano il meccanismo di parentela QT, in particolare avrà come
 * padre la View invocante.
 */
class JSONFilePicker
{

public:
    /**
     * Eliminazione dei costruttori di default per impedire creazione istanze della classe
     */
    explicit JSONFilePicker() = delete;
    explicit JSONFilePicker(const JSONFilePicker&) = delete;
    /**
     * @brief selectJSONFileDialog Mostra l'interfaccia grafica per la selezione di un File
     * Si può selezionare solo un file
     * @return Ritorna il percorso del file selezionato
     */
    static QString selectJSONFileDialog();

    /**
     * @brief getJSONFileData Dato il path di un file ne preleva i dati facendone la lettura, ed interpretandoli come
     * un JSON, la elenaborazione va a buon fine solamente se la path è corretta e se il file è un JSON valido.
     * @param path percorso dove si trova il file
     * @return Documento Json contenente i dati del Json,
     * se documento JSON non valido o path non valida  return QString::isNull() == true
     */
    static QJsonDocument* getJSONFileData(const QString& path);

    /**
     * @brief getMaterialList Metodo che Elabora i Dati JSON e restituisce una lista con i Materiali
     * @param data , Dati JSON da elaborare
     * @return  Lista di QString, ogni elemento è un materiale
     */
    static QStringList* getMaterialList(QJsonDocument* data);

    /**
     * @brief getRecords Metodo che elebora i dati JSON e resituisce un QJsonArray con i record delle stampe
     * @param data, Dati JSon da elaborare
     * @return Records in formato QJsonArray
     */
    static std::list<Record*> getRecords(QJsonDocument* data);

    /**
     * @brief saveAdminModel metodo che dato un documento e una path lo salfa nella
     * path specificata; il documento è in formato QJsonDocument e la path deve essere valida.
     * nel caso non sia valida il metodo ritorna FALSE.
     * Solo nel caso in cui la scrittura vada a buon fine il metodo riorna TRUE.
     * @param doc
     * @param path
     * @return
     */
    static bool saveAdminModel(const QJsonDocument& doc, const QString& path);
};

#endif // JSONFILEPICKER_H
