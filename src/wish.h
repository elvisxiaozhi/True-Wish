#ifndef WISH_H
#define WISH_H

#include "paintedwidget.h"

class Wish : public PaintedWidget
{
    Q_OBJECT
public:
    explicit Wish(PaintedWidget *parent = nullptr, int width = 600);
    ~Wish();

//private:
//    void paintEvent(QPaintEvent *);
};

#endif // WISH_H
