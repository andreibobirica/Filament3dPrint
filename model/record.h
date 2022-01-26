#ifndef RECORD_H
#define RECORD_H

#include <QString>
#include <QDate>

/**
 * @brief The Record class La classe Record è un Modello per una parte specifica di dato.
 * Rapresenta il singolo record di memorizzazione delle stampe 3d,
 * rappresenta una singola stampa 3d e le sue caratteristiche
 */
class Record
{
public:
    /**
     * @brief Record Costruttore
     * @param m Materiale utilizzato per la stampa
     * @param d durata della stampa in ore
     * @param mU grammi di materiale utilizzato
     * @param data Data in cui è stata effettuata la stampa
     */
    explicit Record(QString m, unsigned int d,unsigned int mU,const QDate& data);

    const QString& getMateriale() const;
    unsigned int getDurata() const;
    unsigned int getMatUsato() const;
    const QDate& getData() const;
    //const QString& toString() const;
    void setMateriale(const QString& m){materiale=m;}
    void setDurata(unsigned int d){durata=d;}
    void setMatUsato(unsigned int mu){matUsato=mu;}
    void setData(const QDate& da){data=da;}
private:
    QString materiale;
    unsigned int durata;
    unsigned int matUsato;
    QDate data;
};
#endif // RECORD_H
