#ifndef ADMINMODEL_H
#define ADMINMODEL_H

#include <QJsonDocument>
#include <QString>

#include "model/model.h"
#include "ctrl/jsonfilepicker.h"
#include "model/record.h"

/**
 * @brief The AdminModel class Classe Che si occupa di rappresentare i dati che servono alla schermata Admin, in particolare
 * Elabora i Dati presi da un file JSON, e li memorizza dandogli un significato.
 */
class AdminModel : public Model
{
private:
    QStringList* materialiList;
    std::list<Record*> recordList;
public:
    /**
     * @brief AdminModel Costruttore che viene usato per creare un modello a partire da un Documento Json
     * @param data dati in formato Json
     */
    explicit AdminModel(QJsonDocument* data);
    /**
     * @brief AdminModel Costruttore che viene usato per creare un modello vuoto, senza dati
     */
    explicit AdminModel();

    ~AdminModel() override{qDebug("AdminModel destructed");}
    /**
     * @brief getMaterialList metodo getter
     * @return lista dei materiali QStringList
     */
    QStringList* getMaterialList() const;

    /**
     * @brief getRecordList metodo getter
     * @return lista di Record std::list
     */
    std::list<Record*> getRecordList() const;

    /**
     * @brief removeRecord Metodo che dato un intero rimuove dalla lista di Record l'elemento row-esimo
     * @param row indice dell'elemento da rimuovere
     */
    void removeRecord(unsigned int row);

    /**
     * @brief addRecord Metodo che dato un ptr Record lo aggiunge alla lista di Record*
     * @param r Record* da aggiungere
     */
    void addRecord(Record* r);

    /**
     * @brief getRecordListSize Metodo getter
     * @return gli elementi effettivi all'interno della lista, il numero di record
     */
    unsigned int getRecordListSize();

    /**
     * @brief addMaterial Aggiunge alla QStringList materialList un materiale Qstring m
     * @param m Materiale da agigungere
     */
    void addMaterial(const QString& m);

    /**
     * @brief setMaterial Metodo che modifica un materale eisstente nella materiallIST e lo sostituisce con m
     * @param row indice del materiale da sostituire
     * @param m materiale con cui sostituire
     */
    void setMaterial(unsigned int row, const QString& m);

    /**
     * @brief removeMaterial Rimuove un materiale dalla materialList alla riga==indice row
     * @param row indice del materiale da rimuovere
     */
    void removeMaterial(unsigned int row);

    /**
     * @brief getRecord Metodo getter che restituisce un record specifico dalla record::list
     * @param row indice del Record dalla std::list da restituire
     * @return record da restituire
     */
    Record* getRecord(unsigned int row);
};


#endif // ADMINMODEL_H
