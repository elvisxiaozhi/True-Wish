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
    setBinLable();

    editVec = {wishEdit, goalEdit, timeEdit};

    setFixedHeight(70);
    setStyleSheet("QWidget { background: #414B66; border: 1px solid gray; }");
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
    timeEdit->setWishAttr("How long will it take?");

    ui->timeLayout->insertWidget(0, timeEdit);
}

void WishList::setBinLable()
{
    ui->binWidget->setFixedSize(30, 30);
    binLabel = createBinLabel();
    ui->binLayout->addWidget(binLabel);
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
