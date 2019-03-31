#include "wishlist.h"
#include "ui_wishlist.h"

WishList::WishList(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::WishList)
{
    ui->setupUi(this);

    createWishEdit();
    setStyleSheet("background: #414B66;");
}

WishList::~WishList()
{
    delete ui;
}

void WishList::createWishEdit()
{
    wishEdit = new CustomLineEdit(this);
    wishEdit->setCustomPlaceholderText("What are you wishing for?");

    ui->wishLayout->insertWidget(0, wishEdit);
    ui->wishLine->setFixedSize(200, 1);

    connect(wishEdit, &CustomLineEdit::isFocused, [this](bool isFocused){
        if (isFocused)
            ui->wishLine->setStyleSheet("background-color: white;");
        else
            ui->wishLine->setStyleSheet("background-color: #BFC6D6;");
    });
}

void WishList::mousePressEvent(QMouseEvent *)
{
    wishEdit->clearFocus();
}
