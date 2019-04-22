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
    void setWishWindow(QString, int, int, int, int);

private:
    Ui::Wish *ui;
    QVector<WishList *> wishVec;
    QVector<QFrame *> frameVec;
    CustomLabel *wishLabel;
    const int MIN_HEIGHT = 260, WISH_HEIGHT = 210;

    void createNewWishVec();
    void createWishLabel();
    void mousePressEvent(QMouseEvent *);
    bool allFilled();
    void changeUnderLineToRed();
    void resetLineEdits();

private slots:
    void on_closeButton_clicked();
    void focusIn(CustomLineEdit *);
    void deleteWishList();
    void on_addWishes_clicked();
};

#endif // WISH_H
