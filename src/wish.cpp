#include "wish.h"
#include "ui_wish.h"

Wish::Wish(PaintedWidget *parent, int width) : PaintedWidget(parent, width),
    ui(new Ui::Wish)
{
    ui->setupUi(this);

    addAction("X");
    setOnHoverVec();
    setFixedWidth(870);
    setMinimumHeight(500);
    setStyleSheet("QWidget { background-color: #414B66 }"
                  "#addWishes { background-color: #11B850; border: 0px; padding: 11px 20px; font: 20px; color: white; border-radius: 3px; }"
                  "#addWishes:hover { background-color: #0A863D; }"
                  "#addWishes:pressed { background-color: #0A863D; }");

    createDefaultWishVec();
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
    wishLabel->setFixedSize(70, 70);

    ui->newWishLayout->insertWidget(1, wishLabel);

    connect(wishLabel, &CustomLabel::entered, [this](){ wishLabel->setPixmap(returnBinLabelPixmap(QColor(255, 255, 255), QPixmap(":/icons/add.png"))); });
    connect(wishLabel, &CustomLabel::left, [this](){ wishLabel->setPixmap(QPixmap(":/icons/add.png"));  });
    connect(wishLabel, &CustomLabel::clicked, [this](){ qDebug() << "Clicked"; });
}

void Wish::mousePressEvent(QMouseEvent *event)
{
    commonPressEvent(event);

    int n = wishVec.size();
    for (int i = 0; i < n; ++i) {
        wishVec[i]->clearFocus();
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

void Wish::createDefaultWishVec()
{
    for (int i = 0; i < DEFAULT_WISH_LIST; ++i) {
        WishList *wishList = new WishList(this);
        ui->wishListLayout->addWidget(wishList);
        for (auto e : wishList->editVec) {
            connect(e, &CustomLineEdit::focusIn, [this, e](){ focusIn(e); });
        }

        wishVec.push_back(wishList);
    }
}
