#include "wishlist.h"
#include "ui_wishlist.h"
#include <QDate>

WishList::WishList(PaintedWidget *parent) :
    PaintedWidget(parent),
    ui(new Ui::WishList)
{
    ui->setupUi(this);

    createWishEdit();
    createGoalEdit();
    createTimeEdit();
    setBinLable();

    editVec = {wishEdit, goalEdit, timeEdit};
    for (auto e : editVec) {
        connect(e, &CustomLineEdit::changeUnderLineToRed, this, &WishList::changeUnderLineToRed);
    }

    setStyleSheet("QWidget { background: #414B66; border: 1px solid gray; }");

    /*It's not necessary to set fixed height in this class, just set fixed height for QFrame widget in Wish class*/

//    qDebug() << QDate::currentDate().addYears(1);
}

WishList::~WishList()
{
    delete ui;
}

void WishList::createWishEdit()
{
    wishEdit = new CustomLineEdit(this);
    wishEdit->setWishAttr("What are you wishing for?", false);

    ui->wishLayout->insertWidget(0, wishEdit);
}

void WishList::createGoalEdit()
{
    goalEdit = new CustomLineEdit(this);
    goalEdit->setWishAttr("What is your financial goal?");

    ui->goalLayout->insertWidget(0, goalEdit);
}

void WishList::createTimeEdit()
{
    timeEdit = new CustomLineEdit(this);
    timeEdit->setWishAttr("How long will it take (months)?");

    ui->timeLayout->insertWidget(0, timeEdit);
}

void WishList::setBinLable()
{
    binLabel = createBinLabel();
    binLabel->setStyleSheet("border: none;");
    ui->binLayout->addWidget(binLabel);

    connect(binLabel, &CustomLabel::clicked, [this](){ emit deleteWishList(); });
}

void WishList::changeUnderLineToRed()
{
    QObject *lineEdit = sender();
    for (auto e : editVec) {
        if (e == lineEdit) {
            e->setStyleSheet(CustomLineEdit::styleString.arg("red"));
        }
    }
}

void WishList::clearFocus()
{
    for (auto e : editVec) {
        e->clearFocus();
        emit e->isFocused(false);
    }
}

void WishList::hideBinLabel()
{
    binLabel->hide();
}
