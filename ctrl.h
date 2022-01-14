#ifndef CTRL_H
#define CTRL_H

#include <view.h>

class Ctrl
{
private:
    View* view;
public:
    Ctrl(View* v);
    View* getView() const;
    virtual void showView() const;
    virtual void hideView() const;
};

#endif // CTRL_H
