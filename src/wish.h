#ifndef WISH_H
#define WISH_H

#include "paintedwidget.h"
#include "customlabel.h"
#include "wishlist.h"

namespace Ui {
class Wish;
}

class Wish : public PaintedWidget
{
    Q_OBJECT
public:
    explicit Wish(PaintedWidget *parent = nullptr, int width = 800);
    ~Wish();

private slots:
    void on_closeButton_clicked();

private:
    Ui::Wish *ui;
    WishList *wishList;
    CustomLabel *wishLabel;

    void createWishList();
    void createWishLabel();
};

#endif // WISH_H
