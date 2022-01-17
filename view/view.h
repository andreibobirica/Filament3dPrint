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

signals:
    void viewClosed();

public slots:
};

#endif // VIEW_H
