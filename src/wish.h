#ifndef WISH_H
#define WISH_H

#include "paintedwidget.h"
#include "customlabel.h"
#include "wishlist.h"
#include <QVBoxLayout>

namespace Ui {
class Wish;
}

class Wish : public PaintedWidget
{
    Q_OBJECT
public:
    explicit Wish(PaintedWidget *parent = nullptr, int width = 650);
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
    const int MIN_HEIGHT = 300, WISH_HEIGHT = 210;
    QString origWish, origGoal;
    QVBoxLayout *scrollVLayout;

    void createNewWishVec();
    void createWishLabel();
    void mousePressEvent(QMouseEvent *);
    bool allFilled();
    void changeUnderLineToRed();
    void resetLineEdits();
    bool isWishListEmpty(WishList *);
    void createScrollArea();
    void closeWindow();

private slots:
    void on_closeButton_clicked();
    void focusIn(CustomLineEdit *);
    void deleteWishList();
    void on_addWishes_clicked();
    void on_modifyButton_clicked();
    void wishLabelClicked();
    void on_saveButton_clicked();
    void saveToBeModifiedWishList(bool);
};

#endif // WISH_H
