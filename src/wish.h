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
    const int DEFAULT_WISH_LIST = 3, MIN_HEIGHT = 330, WISH_HEIGHT = 50;

    void createNewWishVec();
    void createWishLabel();
    void mousePressEvent(QMouseEvent *);
    bool allFilled();
    void changeUnderLineToRed();

private slots:
    void focusIn(CustomLineEdit *);
    void deleteWishList();
    void on_addWishes_clicked();
};

#endif // WISH_H
