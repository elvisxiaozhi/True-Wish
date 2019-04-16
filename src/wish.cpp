#include "wish.h"
#include "ui_wish.h"
#include <QVBoxLayout>
#include <QFrame>

Wish::Wish(PaintedWidget *parent, int width) : PaintedWidget(parent, width),
    ui(new Ui::Wish)
{
    ui->setupUi(this);

    addAction("X");
    setOnHoverVec();
    setFixedWidth(600);

    setStyleSheet("QWidget { background-color: #414B66 }"
                  "#addWishes { background-color: #11B850; border: 0px; padding: 11px 20px; font: 20px; color: white; border-radius: 3px; }"
                  "#addWishes:hover { background-color: #0A863D; }"
                  "#addWishes:pressed { background-color: #0A863D; }");

    for (int i = 0; i < DEFAULT_WISH_LIST; ++i) {
        createNewWishVec();
//        wishVec[i]->hideBinLabel(); //default wish vec can not be deleted
    }
    createWishLabel();

    connect(this, &Wish::actionChanged, [this](){ hide(); });

    setFixedHeight(MIN_HEIGHT + WISH_HEIGHT * wishVec.size());
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
    connect(wishLabel, &CustomLabel::clicked, [this](){ createNewWishVec(); setFixedHeight(MIN_HEIGHT + WISH_HEIGHT * wishVec.size()); });
}

void Wish::mousePressEvent(QMouseEvent *event)
{
    commonPressEvent(event);

    int i, n = wishVec.size();
    for (i = 0; i < n; ++i) {
        wishVec[i]->clearFocus();
    }
}

bool Wish::allFilled()
{
    int i;
    for (i = 0; i < DEFAULT_WISH_LIST; ++i) {
        for (auto e : wishVec[i]->editVec) {
            if (e->text().isEmpty()) {
                return false;
            }
        }
    }

    return true;
}

void Wish::changeUnderLineToRed()
{
    int i;
    for (i = 0; i < DEFAULT_WISH_LIST; ++i) {
        for (auto e : wishVec[i]->editVec) {
            if (e->text().isEmpty()) {
                emit e->changeUnderLineToRed();
            }
        }
    }
}

void Wish::focusIn(CustomLineEdit *edit)
{
    int i, n = wishVec.size();
    for (i = 0; i < n; ++i) {
        for (auto e : wishVec[i]->editVec) {
            if (e != edit)
                emit e->isFocused(false);
        }
    }
}

void Wish::deleteWishList()
{
    QObject *wishList = sender();
    int i, n = wishVec.size();
    for (i = 0; i < n; ++i) {
        if (wishList == wishVec[i]) {
            delete wishVec[i]; //delete first
            wishVec.erase(wishVec.begin() + i); //then erase index from vector to prevent out of index issue in MousePressEvent()
            delete frameVec[i];
            frameVec.erase(frameVec.begin() + i);

            setFixedHeight(MIN_HEIGHT + WISH_HEIGHT * wishVec.size()); //delete first, then set fixed height because it needs to use wishVec.size()

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
    QFrame *frame = new QFrame(this);
    frame->setFixedHeight(WISH_HEIGHT);
    frame->setFrameStyle(QFrame::Box);
    frame->setLineWidth(2);
    frame->setStyleSheet("border: 1px solid rbg(46, 41, 41); border-radius: 5px;");
    ui->wishListLayout->addWidget(frame);

    frameVec.push_back(frame);

    WishList *wishList = new WishList(this);
    QVBoxLayout *vLayout = new QVBoxLayout(frame); //set parent to QFrame
    vLayout->setMargin(0);
    vLayout->addWidget(wishList);

    for (auto e : wishList->editVec) {
        connect(e, &CustomLineEdit::focusIn, [this, e](){ focusIn(e); });
    }
    connect(wishList, &WishList::deleteWishList, this, &Wish::deleteWishList);

    wishVec.push_back(wishList);
}

void Wish::on_addWishes_clicked()
{
    if (!allFilled()) {
        changeUnderLineToRed();
    }
}
