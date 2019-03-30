#ifndef WISH_H
#define WISH_H

#include "paintedwidget.h"
#include "customlabel.h"

namespace Ui {
class Wish;
}

class Wish : public PaintedWidget
{
    Q_OBJECT
public:
    explicit Wish(PaintedWidget *parent = nullptr, int width = 600);
    ~Wish();

private:
    Ui::Wish *ui;
    CustomLabel *wishLabel;

    void createWishLabel();
};

#endif // WISH_H
