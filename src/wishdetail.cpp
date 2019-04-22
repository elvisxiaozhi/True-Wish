#include "wishdetail.h"
#include <QVBoxLayout>
#include <QDebug>
#include <QDate>

WishDetail::WishDetail(QWidget *parent) :
    QWidget(parent)
{
    createWishLabel();

    goalBar = new CustomProgressBar(this);
    dateBar = new CustomProgressBar(this);

    QVBoxLayout *vLayout = new QVBoxLayout(this);
    vLayout->addWidget(label);
    vLayout->addWidget(goalBar);
    vLayout->addWidget(dateBar);

    connect(dateBar, &CustomProgressBar::updateToolTip, this, &WishDetail::setDateToolTip);
}

void WishDetail::setWishLableText(QString wish)
{
    label->setText(wish);

    connect(label, &CustomLabel::doubleClicked, [this](){ emit changeWish(); });
}

void WishDetail::setDateBar(QString date, int years, int months, int days)
{
    QDate startDate = QDate::fromString(date, "yyyy-MM-dd");
    QDate endDate = startDate.addYears(years).addMonths(months).addDays(days);
    int daysInTotal = startDate.daysTo(endDate);
    int passedDays = startDate.daysTo(QDate::currentDate());
    daysLeft = daysInTotal - passedDays;

    dateBar->setBarValues(passedDays, daysInTotal);
}

void WishDetail::createWishLabel()
{
    label = new CustomLabel(this);
    label->setStyleSheet("background-color: #11B850; border: 0px; padding: 15px 20px; font: 20px; color: white; border-radius: 3px;");
    label->setTextFormat(Qt::RichText);
}

void WishDetail::setDateToolTip()
{
    dateBar->toolTip = QString::number(daysLeft) + " days left";
}
