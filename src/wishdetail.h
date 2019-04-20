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

private:
    CustomLabel *label;
    CustomProgressBar *progressBar;

    void createWishLabel();
};

#endif // WISHDETAIL_H
