#ifndef VIEW_H
#define VIEW_H

#include <QWidget>
#include <QSize>

class View : public QWidget
{
    Q_OBJECT
private:
    QSize* windowSize;
public:
    explicit View(QSize* s = nullptr);
    void setWindowSize(QSize*);
    QSize* getWindowSize() const;
    void applyWindowSize(QSize*);

signals:

public slots:
};

#endif // VIEW_H
