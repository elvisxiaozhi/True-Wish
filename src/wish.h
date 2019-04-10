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
    explicit Wish(PaintedWidget *parent = nullptr, int width = 870);
    ~Wish();

private slots:
    void on_closeButton_clicked();

private:
    Ui::Wish *ui;
    QVector<WishList *> wishVec;
    CustomLabel *wishLabel;

    void createWishVec();
    void createWishLabel();
    void mousePressEvent(QMouseEvent *);
    void connectWishEdit();

private slots:
    void focusIn(CustomLineEdit *);
};

#endif // WISH_H
