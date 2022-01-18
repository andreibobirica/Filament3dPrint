#ifndef VIEW_H
#define VIEW_H

#include <QWidget>
#include <QSize>

/**
 * @brief The View class
 * Classe che serve a rappresentare una View,
 */
class View : public QWidget
{
    Q_OBJECT
private:
    QSize* windowSize;

    /**
     * @brief connectViewSignals Interfaccia da implementare nelle classi derivate
     * Questo Metodo serve a dare l'interfaccia per le future implementazioni specifiche che connetteranno
     * i SIGNAL dei singoli elementi grafici (QPushButton, etc..) ai propri segnali della View.
     * I segnali della view saranno gli unici a comunicare con il Controller.
     */
    virtual void connectViewSignals() const = 0;

public:
    /**
     * @brief View Costruttore della view che si occupa ad impostare la sua windowSize e ad applicarla
     * @param s Grandezza della finistra, la windowSize
     */
    explicit View(QSize* s = nullptr,View* parent = nullptr);

    virtual ~View() {qDebug("View destructed");}

    /**
     * @brief setWindowSize
     * Metodo setter del campo windowsize
     */
    void setWindowSize(QSize*);
    /**
     * @brief getWindowSize Metodo getter della windowSize
     * @return windowSize, gradezza della finestra della view
     */
    QSize* getWindowSize() const;
    /**
     * @brief applyWindowSize
     * Metodo che serve ad applicare la windowSize alla View e modificarne effettivamente la dimensione
     */
    void applyWindowSize(QSize*);

    /**
     * @brief showQuestionDialog Questo metodo mostra un popup a schermo con stile di domanda
     * e ne interpreta l'interazione.
     * @param paramNum numero di parametri tra cui si vuole scegliere, fondamentalmente
     * si sceglie se si vuole avere Cancel No Yes tra le opzioni.
     * 2 = No Yes
     * 3 = default = Cancel No Yes
     * @param title Titolo del popUp
     * @param info Messaggio Informativo da mostrare
     * @return valore boolerano == true sse si è premuto su Yes
     */
    bool showQuestionDialog(unsigned int paramNum, const QString& title,const QString& info);

    /**
     * @brief showWarningDialog Mostra un pop informativo che non interaziona in maniera fondamentale col utente.
     * Richiede solo la pressione di Ok.
     * @param mes messaggio da mostrare
     * @param mesInfo messaggio specifico da mostrare
     */
    void showWarningDialog(const QString &mes, const QString &mesInfo);
signals:
    void viewClosed();

public slots:
};

#endif // VIEW_H
