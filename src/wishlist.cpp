#include "wishlist.h"
#include "ui_wishlist.h"

WishList::WishList(PaintedWidget *parent) :
    PaintedWidget(parent),
    ui(new Ui::WishList)
{
    ui->setupUi(this);

    createWishEdit();
    createGoalEdit();
    createTimeEdit();

    editVec = {wishEdit, goalEdit, timeEdit};

    setFixedHeight(70);
    setStyleSheet("background: #414B66; border: 1px solid gray");
}

WishList::~WishList()
{
    delete ui;
}

void WishList::createWishEdit()
{
    wishEdit = new CustomLineEdit(this);
    wishEdit->setWishAttr("What are you wishing for?");

    ui->wishLayout->insertWidget(0, wishEdit);
    ui->wishLine->setFixedSize(250, 1);

    wishEdit->changeFocuseEffect(ui->wishLine);
}

void WishList::createGoalEdit()
{
    goalEdit = new CustomLineEdit(this);
    goalEdit->setWishAttr("What is your financial goal?");

    ui->goalLayout->insertWidget(0, goalEdit);
    ui->goalLine->setFixedSize(250, 1);

    goalEdit->changeFocuseEffect(ui->goalLine);
}

void WishList::createTimeEdit()
{
    timeEdit = new CustomLineEdit(this);
    timeEdit->setWishAttr("How long will it take?");

    ui->timeLayout->insertWidget(0, timeEdit);
    ui->timeLine->setFixedSize(250, 1);

    timeEdit->changeFocuseEffect(ui->timeLine);
}

void WishList::clearFocus()
{
    for (auto e : editVec) {
        e->clearFocus();
        emit e->isFocused(false);
    }
}
