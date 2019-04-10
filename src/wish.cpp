#include "wish.h"
#include "ui_wish.h"

Wish::Wish(PaintedWidget *parent, int width) : PaintedWidget(parent, width),
    ui(new Ui::Wish)
{
    ui->setupUi(this);

    addAction("X");
    setOnHoverVec();
    setFixedWidth(870);
    setMinimumHeight(900);
    setStyleSheet("background-color: #414B66");

    createWishVec();
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

    connect(wishLabel, &CustomLabel::entered, [this](){ wishLabel->setPixmap(returnBinLabelPixmap(QColor(255, 255, 255), QPixmap(":/icons/add.png"))); });
    connect(wishLabel, &CustomLabel::left, [this](){ wishLabel->setPixmap(QPixmap(":/icons/add.png"));  });
}

void Wish::mousePressEvent(QMouseEvent *event)
{
    commonPressEvent(event);

    int n = wishVec.size();
    for (int i = 0; i < n; ++i) {
        wishVec[i]->clearFocus();
    }
}

void Wish::connectWishEdit()
{
    int n = wishVec.size();
    for (int i = 0; i < n; ++i) {
        for (auto e : wishVec[i]->editVec) {
            connect(e, &CustomLineEdit::focusIn, [this, e](){ focusIn(e); });
        }
    }
}

void Wish::focusIn(CustomLineEdit *edit)
{
    int n = wishVec.size();
    for (int i = 0; i < n; ++i) {
        for (auto e : wishVec[i]->editVec) {
            if (e != edit)
                emit e->isFocused(false);
        }
    }
}

void Wish::on_closeButton_clicked()
{
    hide();
}

void Wish::createWishVec()
{
    for (int i = 0; i < 3; ++i) {
        WishList *wishList = new WishList(this);
        ui->wishListLayout->addWidget(wishList);
        wishVec.push_back(wishList);
    }

    connectWishEdit();
}
