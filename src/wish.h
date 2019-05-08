#ifndef WISH_H
#define WISH_H

#include "paintedwidget.h"
#include "customlabel.h"
#include "wishlist.h"
#include <QVBoxLayout>

namespace Ui {
class Wish;
}

using std::tuple;

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

    QVector<tuple<QString, int, int, int, int> > getGetWishes() const;
    void setGetWishes(const QVector<tuple<QString, int, int, int, int> > &value);

private:
    Ui::Wish *ui;
    QVector<WishList *> wishVec;
    QVector<tuple<QString, int, int, int, int> > wishListValues;
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
    QVector<tuple<QString, int, int, int, int> > getWishes();
    void printVec(QVector<tuple<QString, int, int, int, int> >); //delete later

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
