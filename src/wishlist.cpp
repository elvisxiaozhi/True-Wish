#include "wishlist.h"
#include "ui_wishlist.h"

WishList::WishList(PaintedWidget *parent) :
    PaintedWidget(parent),
    ui(new Ui::WishList)
{
    ui->setupUi(this);

    binLabel = createBinLabel();
    binLabel->setPixmap(QPixmap(":/icons/recycle bin.png"));
    binLabel->show();
    ui->binLayout->addWidget(binLabel);

    createWishEdit();
    createGoalEdit();
    createTimeEdit();
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
    connect(wishEdit, &CustomLineEdit::focusIn, [this](){ emit goalEdit->isFocused(false);  emit timeEdit->isFocused(false); });
}

void WishList::createGoalEdit()
{
    goalEdit = new CustomLineEdit(this);
    goalEdit->setWishAttr("What is your financial goal?");

    ui->goalLayout->insertWidget(0, goalEdit);
    ui->goalLine->setFixedSize(250, 1);

    goalEdit->changeFocuseEffect(ui->goalLine);
    connect(goalEdit, &CustomLineEdit::focusIn, [this](){ emit wishEdit->isFocused(false);  emit timeEdit->isFocused(false); });
}

void WishList::createTimeEdit()
{
    timeEdit = new CustomLineEdit(this);
    timeEdit->setWishAttr("How long will it take?");

    ui->timeLayout->insertWidget(0, timeEdit);
    ui->timeLine->setFixedSize(250, 1);

    timeEdit->changeFocuseEffect(ui->timeLine);
    connect(timeEdit, &CustomLineEdit::focusIn, [this](){ emit wishEdit->isFocused(false);  emit goalEdit->isFocused(false); });
}

void WishList::clearFocus()
{
    wishEdit->clearFocus();
    goalEdit->clearFocus();
    timeEdit->clearFocus();

    emit wishEdit->isFocused(false);
    emit goalEdit->isFocused(false);
    emit timeEdit->isFocused(false);
}
