#include "wish.h"
#include "ui_wish.h"
#include <QVBoxLayout>
#include <QFrame>
#include <QDate>
#include "core/database.h"
#include <QDate>

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

    createNewWishVec();
    wishVec.first()->hideBinLabel(); //default wish vec can not be deleted
    createWishLabel();

    connect(this, &Wish::actionChanged, [this](){ hide(); });

    setFixedHeight(MIN_HEIGHT + WISH_HEIGHT * wishVec.size());
}

Wish::~Wish()
{
    delete ui;
}

void Wish::setWishWindow(QString wish, int goal, int years, int months, int days)
{
    WishList *w = wishVec.first();
    w->editVec[0]->setText(wish);
    w->editVec[1]->setText(QString::number(goal));
    w->editVec[2]->setText(QString::number(years));
    w->editVec[3]->setText(QString::number(months));
    w->editVec[4]->setText(QString::number(days));
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
    for (auto wish : wishVec) {
        //make sure that years, months and days line edit has at least one being filled with text
        if (wish->editVec[2]->text().isEmpty() && wish->editVec[3]->text().isEmpty() && wish->editVec[4]->text().isEmpty()) {
            return false;
        }
        else {
            int i;
            for (i = 0; i < 2; ++i) {
                if (wish->editVec[i]->text().isEmpty())
                    return false;
            }
        }
    }

    return true;
}

void Wish::changeUnderLineToRed()
{
    for (auto wish : wishVec) {
        for (auto e : wish->editVec) {
            if (e->text().isEmpty()) {
                emit e->changeUnderLineToRed();
            }
        }
    }
}

void Wish::resetLineEdits()
{
    for (auto wish : wishVec) {
        for (auto e : wish->editVec) {
            e->clear();
            emit e->isFocused(false);
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
    frame->setStyleSheet("QFrame {border: 1px solid rbg(46, 41, 41); border-radius: 5px; }"); //set border-radius in QFrame, or all child widgets will be applyed
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
    else {
        for (auto e : wishVec) {
            QString wish = e->editVec[0]->text();
            int goal = e->editVec[1]->text().toInt();
            int years = e->editVec[2]->text().toInt();
            int months = e->editVec[3]->text().toInt();
            int days = e->editVec[4]->text().toInt();
            Database::addWish(QDate::currentDate().toString("yyyy-MM-dd"), wish, goal, years, months, days);

            resetLineEdits();
            close();
        }
    }
}
