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

#include <view.h>

class AdminView : public View
{
    Q_OBJECT
private:
    QGridLayout* mainLayout;
public:
    explicit AdminView(QSize* s = nullptr);

signals:

public slots:
};

#endif // ADMINVIEW_H
