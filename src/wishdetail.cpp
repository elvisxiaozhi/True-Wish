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
    hLayout->addWidget(prevLbl);
    hLayout->addLayout(vLayout);
    hLayout->addWidget(nextLbl);

    connect(goalBar, &CustomProgressBar::updateToolTip, this, &WishDetail::setGoalBarDetail);
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

    setGoalBarDetail(); //this is will make a difference when moneyNeeded <= 0
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

pair<QString, int> WishDetail::returnWishDetail()
{
    pair<QString, int> res = std::make_pair(wishLbl->text(), goalBar->maximum());

    return res;
}

void WishDetail::setChangeWishLblVis(int index, int last)
{
    prevLbl->show();
    nextLbl->show();
    if (index == 0) {
        prevLbl->hide();
    }
    else if (index == last) {
        nextLbl->hide();
    }
}

void WishDetail::createWishLabel()
{
    wishLbl = new CustomLabel(this);
    wishLbl->setStyleSheet("background-color: #11B850; border: 0px; padding: 15px 20px; font: 20px; color: white; border-radius: 3px;");
    wishLbl->setTextFormat(Qt::RichText);
}

void WishDetail::createChangeWishLabels()
{
    prevLbl = new CustomLabel(this);
    prevLbl->setPixmap(QPixmap(":/icons/left arrow 64px.png"));
    nextLbl = new CustomLabel(this);
    nextLbl->setPixmap(QPixmap(":/icons/right arrow 64px.png"));

    connect(prevLbl, &CustomLabel::entered, [this](){ prevLbl->setStyleSheet("background:	#414B66"); });
    connect(prevLbl, &CustomLabel::left, [this](){ prevLbl->setStyleSheet(""); });
    connect(prevLbl, &CustomLabel::clicked, [this](){ emit prevWish(); });
    connect(nextLbl, &CustomLabel::entered, [this](){ nextLbl->setStyleSheet("background: #414B66"); });
    connect(nextLbl, &CustomLabel::left, [this](){ nextLbl->setStyleSheet(""); });
    connect(nextLbl, &CustomLabel::clicked, [this](){ emit nextWish(); });
    connect(this, &WishDetail::hidePrevLbl, [this](bool isHidden){
        if (isHidden)
            prevLbl->hide();
        else
            prevLbl->show();
    });
    connect(this, &WishDetail::hideNextLbl, [this](bool isHidden){
        if (isHidden)
            nextLbl->hide();
        else
            nextLbl->show();
    });
}

void WishDetail::setGoalBarDetail()
{
    if (moneyNeeded > 0) {
        goalBar->toolTip = QString::number(moneyNeeded) + " needed";
    }
    else {
        goalBar->setBarValues(goalBar->maximum(), goalBar->maximum());
        goalBar->setFormat("Goal accomplished");
        goalBar->toolTip = QString::number(goalBar->maximum()) + " saved";
    }
}
