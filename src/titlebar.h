#ifndef TITLEBAR_H
#define TITLEBAR_H

#include "paintedwidget.h"

class TitleBar : public PaintedWidget
{
    Q_OBJECT
public:
    explicit TitleBar(PaintedWidget *parent = nullptr, int width = 1250);

private:
    void paintEvent(QPaintEvent *);
};

#endif // TITLEBAR_H
