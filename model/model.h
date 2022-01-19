#ifndef MODEL_H
#define MODEL_H

#include <QDebug>

class Model
{

public:
    explicit Model();

    virtual ~Model() {qDebug("Model destructed");}
};

#endif // MODEL_H
