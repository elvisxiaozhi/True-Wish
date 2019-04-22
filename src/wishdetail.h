#ifndef WISHDETAIL_H
#define WISHDETAIL_H

#include <QWidget>
#include "customprogressbar.h"
#include "customlabel.h"

class WishDetail : public QWidget
{
    Q_OBJECT

public:
    explicit WishDetail(QWidget *parent = 0);
    void setWishLableText(QString);
    void setDateBar(QString, int, int, int);

private:
    CustomLabel *label;
    CustomProgressBar *goalBar, *dateBar;
    int daysLeft;

    void createWishLabel();

signals:
    void changeWish();

private slots:
    void setDateToolTip();
};

#endif // WISHDETAIL_H
