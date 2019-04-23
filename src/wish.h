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
    explicit Wish(PaintedWidget *parent = nullptr, int width = 600);
    ~Wish();

public:
    void setWishInfo(QString, int, int, int, int);
    void setAddWishWindow();
    void setChangeWishWindow();

private:
    Ui::Wish *ui;
    QVector<WishList *> wishVec;
    QVector<QFrame *> frameVec;
    CustomLabel *wishLabel;
    const int MIN_HEIGHT = 260, WISH_HEIGHT = 210;
    QString origWish, origGoal;

    void createNewWishVec();
    void createWishLabel();
    void mousePressEvent(QMouseEvent *);
    bool allFilled();
    void changeUnderLineToRed();
    void resetLineEdits();
    bool isWishListEmpty(WishList *);
    void removeEmptyWishList();

private slots:
    void on_closeButton_clicked();
    void focusIn(CustomLineEdit *);
    void deleteWishList();
    void on_addWishes_clicked();
    void on_modifyButton_clicked();
    void wishLabelClicked();
};

#endif // WISH_H
