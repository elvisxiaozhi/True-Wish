#include "wish.h"
#include "ui_wish.h"

Wish::Wish(PaintedWidget *parent, int width) : PaintedWidget(parent, width),
    ui(new Ui::Wish)
{
    ui->setupUi(this);

    addAction("X");
    setOnHoverVec();
    setFixedWidth(800);
    setMinimumHeight(600);
    setStyleSheet("background-color: #414B66");

    createWishList();
    createWishLabel();

    connect(this, &Wish::actionChanged, [this](){ hide(); });
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

void Wish::on_closeButton_clicked()
{
    hide();
}

void Wish::createWishList()
{
    wishList = new WishList(this);
    ui->wishListLayout->addWidget(wishList);
}
