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

    createChangeWishLabels();

    QVBoxLayout *vLayout = new QVBoxLayout;
    vLayout->addWidget(wishLbl);
    vLayout->addWidget(goalBar);
    vLayout->addWidget(dateBar);

    QHBoxLayout *hLayout = new QHBoxLayout(this);
    hLayout->addWidget(forwardLbl);
    hLayout->addLayout(vLayout);
    hLayout->addWidget(backwardLbl);

    connect(goalBar, &CustomProgressBar::updateToolTip, [this](){ goalBar->toolTip = QString::number(moneyNeeded) + " needed"; });
    connect(dateBar, &CustomProgressBar::updateToolTip, [this](){ dateBar->toolTip = QString::number(daysLeft) + " days left"; });
}

void WishDetail::setWishLableText(QString wish)
{
    wishLbl->setText(wish);

    connect(wishLbl, &CustomLabel::doubleClicked, [this](){ emit changeWish(); });
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

tuple<QString, QString, int, int, int, int> WishDetail::returnWishDetail()
{
//    tuple<QString, QString, int, int, int, int> res = make_tuple(wishLbl->text(), );


}

void WishDetail::createWishLabel()
{
    wishLbl = new CustomLabel(this);
    wishLbl->setStyleSheet("background-color: #11B850; border: 0px; padding: 15px 20px; font: 20px; color: white; border-radius: 3px;");
    wishLbl->setTextFormat(Qt::RichText);
}

void WishDetail::createChangeWishLabels()
{
    forwardLbl = new CustomLabel(this);
    forwardLbl->setPixmap(QPixmap(":/icons/left arrow 64px.png"));
    backwardLbl = new CustomLabel(this);
    backwardLbl->setPixmap(QPixmap(":/icons/right arrow 64px.png"));

    connect(forwardLbl, &CustomLabel::entered, [this](){ forwardLbl->setStyleSheet("background:	#414B66"); });
    connect(forwardLbl, &CustomLabel::left, [this](){ forwardLbl->setStyleSheet(""); });
    connect(forwardLbl, &CustomLabel::clicked, [this](){ emit prevWish(); });
    connect(backwardLbl, &CustomLabel::entered, [this](){ backwardLbl->setStyleSheet("background: #414B66"); });
    connect(backwardLbl, &CustomLabel::left, [this](){ backwardLbl->setStyleSheet(""); });
    connect(backwardLbl, &CustomLabel::clicked, [this](){ emit nextWish(); });
}
