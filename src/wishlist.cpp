#include "wishlist.h"
#include "ui_wishlist.h"

WishList::WishList(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::WishList)
{
    ui->setupUi(this);

    createWishEdit();
    createGoalEdit();
    setFixedHeight(70);
    setStyleSheet("background: #414B66;");
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

void WishList::clearFocus()
{
    wishEdit->clearFocus();
    goalEdit->clearFocus();

    emit wishEdit->isFocused(false);
    emit goalEdit->isFocused(false);
}
