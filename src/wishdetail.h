#ifndef WISHDETAIL_H
#define WISHDETAIL_H

#include <QWidget>
#include "customprogressbar.h"
#include "customlabel.h"
#include <QSpacerItem>

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
    QSpacerItem *prevSpacer, *nextSpacer;
    CustomProgressBar *goalBar, *dateBar;
    int daysLeft, moneyNeeded;
    const int FIXED_WIDTH = 65;

    void createWishLabel();
    void createChangeWishLabels();
    void setSpacerSize(QSpacerItem *, bool);

signals:
    void changeWish();
    void prevWish();
    void nextWish();
    void hidePrevLbl(bool isHidden = true);
    void hideNextLbl(bool isHidden = true);

private slots:
    void setGoalBarDetail();
    void setPrevLblVis(bool);
    void setNextLblVis(bool);
};

#endif // WISHDETAIL_H
