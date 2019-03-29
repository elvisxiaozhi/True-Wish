#ifndef WISH_H
#define WISH_H

#include "paintedwidget.h"

class Wish : public PaintedWidget
{
    Q_OBJECT
public:
    explicit Wish(PaintedWidget *parent = nullptr, int width = 1200);

private:
    void paintEvent(QPaintEvent *) override;
};

#endif // WISH_H
