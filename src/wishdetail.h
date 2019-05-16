#ifndef WISHDETAIL_H
#define WISHDETAIL_H

#include <QWidget>
#include "customprogressbar.h"
#include "customlabel.h"

using std::pair;

class WishDetail : public QWidget
{
    Q_OBJECT

public:
    explicit WishDetail(QWidget *parent = 0);
    void setWishLableText(QString);
    void setGoalBar(QString, int);
    void setDateBar(QString, int, int, int);
    pair<QString, int> returnWishDetail();
    void setChangeWishLblVis(int, int); //change prevLbl and nextLbl visibility

private:
    CustomLabel *wishLbl, *prevLbl, *nextLbl;
    CustomProgressBar *goalBar, *dateBar;
    int daysLeft, moneyNeeded;

    void createWishLabel();
    void createChangeWishLabels();

signals:
    void changeWish();
    void prevWish();
    void nextWish();
    void hidePrevLbl(bool isHidden = true);
    void hideNextLbl(bool isHidden = true);
};

#endif // WISHDETAIL_H
