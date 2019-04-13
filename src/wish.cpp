#include "wish.h"
#include "ui_wish.h"

int Wish::WISH_VEC_SIZE = 0;

Wish::Wish(PaintedWidget *parent, int width) : PaintedWidget(parent, width),
    ui(new Ui::Wish)
{
    ui->setupUi(this);

    addAction("X");
    setOnHoverVec();
    setFixedWidth(870);
    setStyleSheet("QWidget { background-color: #414B66 }"
                  "#addWishes { background-color: #11B850; border: 0px; padding: 11px 20px; font: 20px; color: white; border-radius: 3px; }"
                  "#addWishes:hover { background-color: #0A863D; }"
                  "#addWishes:pressed { background-color: #0A863D; }");

    for (int i = 0; i < DEFAULT_WISH_LIST; ++i) {
        createNewWishVec();
        wishVec[i]->hideBinLabel(); //default wish vec can not be deleted
    }
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
    connect(wishLabel, &CustomLabel::clicked, [this](){ createNewWishVec(); });
}

void Wish::mousePressEvent(QMouseEvent *event)
{
    commonPressEvent(event);

    //use WISH_VEC_SIZE instead of wishVec.size() to prevent the program from crashing
    int i;
    for (i = 0; i < WISH_VEC_SIZE; ++i) {
        wishVec[i]->clearFocus();
    }
}


void Wish::focusIn(CustomLineEdit *edit)
{
    int i;
    for (i = 0; i < WISH_VEC_SIZE; ++i) {
        for (auto e : wishVec[i]->editVec) {
            if (e != edit)
                emit e->isFocused(false);
        }
    }
}

void Wish::deleteWishList()
{
    QObject *wishList = sender();
    int i;
    for (i = 0; i < WISH_VEC_SIZE; ++i) {
        if (wishList == wishVec[i]) {
            qDebug() << i;
            wishVec[i]->deleteLater();
//            delete wishVec[i];
            --WISH_VEC_SIZE;
            break;
        }
    }
}

void Wish::on_closeButton_clicked()
{
    hide();
}

void Wish::createNewWishVec()
{
    WishList *wishList = new WishList(this);
    ui->wishListLayout->addWidget(wishList);

    ++WISH_VEC_SIZE;

    for (auto e : wishList->editVec) {
        connect(e, &CustomLineEdit::focusIn, [this, e](){ focusIn(e); });
    }
    connect(wishList, &WishList::deleteWishList, this, &Wish::deleteWishList);

    wishVec.push_back(wishList);
}
