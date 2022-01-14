#ifndef HOMEVIEW_H
#define HOMEVIEW_H

#include <QWidget>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QPushButton>
#include <QLabel>
#include <QPixmap>

#include <view.h>

class HomeView : public View
{
    Q_OBJECT
private:
    QHBoxLayout* mainLayout;
    QPushButton* newPButton;
    QPushButton* openPButton;

    QLayout* createButtonsLayout();
    QLayout* createDescriptionLayout(const QString&,const QString&);
protected:
    QHBoxLayout* getMainLayout() const;

public:
    explicit HomeView(QSize* s = new QSize(720,480));

signals:

public slots:
};

#endif // HOMEVIEW_H
