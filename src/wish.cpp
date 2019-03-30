#include "wish.h"
#include "ui_wish.h"

Wish::Wish(PaintedWidget *parent, int width) : PaintedWidget(parent, width),
    ui(new Ui::Wish)
{
    ui->setupUi(this);

    addAction("X");
    setOnHoverVec();
    setStyleSheet("background-color: #414B66");

    createWishLabel();
}

Wish::~Wish()
{
    delete ui;
}

void Wish::createWishLabel()
{
    wishLabel = new CustomLabel(this);
    wishLabel->setPixmap(QPixmap(":/icons/add.png"));

    ui->newWishLayout->insertWidget(1, wishLabel);
}
