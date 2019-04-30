#include "wishdetail.h"
#include <QVBoxLayout>
#include <QDebug>
#include <QDate>
#include "core/database.h"

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

    connect(goalBar, &CustomProgressBar::updateToolTip, [this](){ goalBar->toolTip = QString::number(moneyNeeded) + " needed"; });
    connect(dateBar, &CustomProgressBar::updateToolTip, [this](){ dateBar->toolTip = QString::number(daysLeft) + " days left"; });
}

void WishDetail::setWishLableText(QString wish)
{
    label->setText(wish);

    connect(label, &CustomLabel::doubleClicked, [this](){ emit changeWish(); });
}

void WishDetail::setGoalBar(QString date, int goal)
{
    int saved = Database::countSavedMoney(date, QDate::currentDate().toString("yyyy-MM-dd"));
    moneyNeeded = goal - saved;

    goalBar->setBarValues(saved, goal);
}

void WishDetail::setDateBar(QString date, int years, int months, int days)
{
    QDate startDate = QDate::fromString(date, "yyyy-MM-dd");
    QDate endDate = startDate.addYears(years).addMonths(months).addDays(days);
    int daysInTotal = startDate.daysTo(endDate);
    int passedDays = startDate.daysTo(QDate::currentDate());
    daysLeft = daysInTotal - passedDays;

    dateBar->setBarValues(passedDays, daysInTotal, true);
}

void WishDetail::createWishLabel()
{
    label = new CustomLabel(this);
    label->setStyleSheet("background-color: #11B850; border: 0px; padding: 15px 20px; font: 20px; color: white; border-radius: 3px;");
    label->setTextFormat(Qt::RichText);
}
