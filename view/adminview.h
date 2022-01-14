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
public:
    /**
     * @brief AdminView
     * Costruttore della Admin View
     * @param s windowSize, grandezza della finestra della View
     */
    explicit AdminView(QSize* s = nullptr);

signals:

public slots:
};

#endif // ADMINVIEW_H
