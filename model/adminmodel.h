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

};


#endif // ADMINMODEL_H
