#ifndef WISHDETAIL_H
#define WISHDETAIL_H

#include <QWidget>
#include "customprogressbar.h"
#include "customlabel.h"

using std::tuple;

class WishDetail : public QWidget
{
    Q_OBJECT

public:
    explicit WishDetail(QWidget *parent = 0);
    void setWishLableText(QString);
    void setGoalBar(QString, int);
    void setDateBar(QString, int, int, int);
    tuple<QString, QString, int, int, int, int> returnWishDetail();

private:
    CustomLabel *wishLbl, *forwardLbl, *backwardLbl;
    CustomProgressBar *goalBar, *dateBar;
    int daysLeft, moneyNeeded;

    void createWishLabel();
    void createChangeWishLabels();

signals:
    void changeWish();
    void prevWish();
    void nextWish();

private slots:
};

#endif // WISHDETAIL_H
