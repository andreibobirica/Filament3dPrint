#ifndef MODEL_H
#define MODEL_H

#include <QObject>

class Model : public QObject
{
    Q_OBJECT
public:
    explicit Model();

    virtual ~Model() {qDebug("Model destructed");}

signals:

public slots:
};

#endif // MODEL_H
