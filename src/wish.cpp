#include "wish.h"
#include "ui_wish.h"
#include <QFrame>
#include <QDate>
#include "core/database.h"
#include <QDate>
#include <QScrollArea>

Wish::Wish(PaintedWidget *parent, int width) : PaintedWidget(parent, width),
    ui(new Ui::Wish)
{
    ui->setupUi(this);

    addAction("X");
    setOnHoverVec();
    setFixedWidth(650);

    createScrollArea();

    setStyleSheet("QWidget { background-color: #414B66 }"
                  "#addWishes, #modifyButton, #saveButton { background-color: #11B850; border: 0px; padding: 11px 20px; font: 20px; color: white; border-radius: 3px; }"
                  "#addWishes:hover, #modifyButton:hover { background-color: #0A863D; }"
                  "#addWishes:pressed, #modifyButton:pressed { background-color: #0A863D; }"
                  "QScrollBar:vertical { width: 2px; background: #CED8E2; }"
                  "QScrollBar::handle:vertical { background: #414B66; }"
                  );

    createNewWishVec();
    wishVec.first()->isBinLabelHidden(false); //default wish vec can not be deleted
    createWishLabel();

    connect(this, &Wish::actionChanged, [this](){ removeEmptyWishList(); close(); }); //remove first, then call close()

    setFixedHeight(MIN_HEIGHT + WISH_HEIGHT * wishVec.size());
}

Wish::~Wish()
{
    delete ui;
}

void Wish::setWishInfo(QString wish, int goal, int years, int months, int days)
{
    WishList *w = wishVec.first();
    w->editVec[0]->setText(wish);
    w->editVec[1]->setText(QString::number(goal));
    w->editVec[2]->setText(QString::number(years));
    w->editVec[3]->setText(QString::number(months));
    w->editVec[4]->setText(QString::number(days));

    origWish = wish;
    origGoal = goal;
}

void Wish::setAddWishWindow()
{
    ui->title->setText("Add Wishes");
    ui->addWishes->show();
    ui->modifyButton->hide();
    ui->saveButton->hide();
    wishVec.first()->isBinLabelHidden(false);
}

void Wish::setChangeWishWindow()
{
    ui->title->setText("Change Wishes");
    ui->modifyButton->show();
    ui->addWishes->hide();
    ui->saveButton->hide();
    wishVec.first()->isBinLabelHidden(true);
}

void Wish::createWishLabel()
{
    wishLabel = new CustomLabel(this);
    wishLabel->setPixmap(QPixmap(":/icons/add.png"));
    wishLabel->setFixedSize(70, 70);

    ui->newWishLayout->insertWidget(1, wishLabel);

    connect(wishLabel, &CustomLabel::entered, [this](){ wishLabel->setPixmap(returnBinLabelPixmap(QColor(255, 255, 255), QPixmap(":/icons/add.png"))); });
    connect(wishLabel, &CustomLabel::left, [this](){ wishLabel->setPixmap(QPixmap(":/icons/add.png"));  });
    connect(wishLabel, &CustomLabel::clicked, this, &Wish::wishLabelClicked);
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

bool Wish::isWishListEmpty(WishList *wishList)
{
    for (auto e : wishList->editVec) {
        if (!e->text().isEmpty()) {
            return false;
        }
    }

    return true;
}

void Wish::removeEmptyWishList()
{
    for (auto wishList : wishVec) {
        if (isWishListEmpty(wishList)) {
            wishList->emitBinLabelClickedSignal();
        }
    }
}

void Wish::createScrollArea()
{
    QScrollArea *scrollArea = new QScrollArea(this);
    scrollArea->setBackgroundRole(QPalette::Window);
    scrollArea->setFrameShadow(QFrame::Plain);
    scrollArea->setFrameShape(QFrame::NoFrame);
    scrollArea->setWidgetResizable(true);
    scrollArea->setMaximumHeight((WISH_HEIGHT + 15) * 2);

    ui->wishListLayout->addWidget(scrollArea);

    scrollVLayout = new QVBoxLayout;

    QWidget *scrollWidget = new QWidget(this); //need scrollWidget to set handle
    scrollWidget->setLayout(scrollVLayout);

    scrollArea->setWidget(scrollWidget);
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

            setFixedHeight(MIN_HEIGHT + WISH_HEIGHT * wishVec.size());

            break;
        }
    }

    if (wishVec.size() == 1) { //need to change 1 here later
        ui->modifyButton->show();
        ui->addWishes->hide();
        ui->saveButton->hide();
    }
}

void Wish::on_closeButton_clicked()
{
    removeEmptyWishList();
    close();
}

void Wish::createNewWishVec()
{
    QFrame *frame = new QFrame(this);
    frame->setFixedHeight(WISH_HEIGHT);
    frame->setFrameStyle(QFrame::Box);
    frame->setLineWidth(2);
    frame->setStyleSheet("QFrame {border: 1px solid rbg(46, 41, 41); border-radius: 5px; }"); //set border-radius in QFrame, or all child widgets will be applyed
    scrollVLayout->addWidget(frame);

    frameVec.push_back(frame);

    WishList *wishList = new WishList(this);
    QVBoxLayout *vLayout = new QVBoxLayout(frame); //set parent to QFrame
    vLayout->setMargin(0);
    vLayout->addWidget(wishList);

    for (auto e : wishList->editVec) {
        connect(e, &CustomLineEdit::focusIn, [this, e](){ focusIn(e); });
    }
    connect(wishList, &WishList::deleteWishList, this, &Wish::deleteWishList);
    connect(wishList, &WishList::lineEditTextEdited, this, &Wish::saveToBeModifiedWishList);

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

void Wish::on_modifyButton_clicked()
{
//    WishList *e = wishVec.first(); //mofify here later

//    QString wish = e->editVec[0]->text();
//    int goal = e->editVec[1]->text().toInt();
//    int years = e->editVec[2]->text().toInt();
//    int months = e->editVec[3]->text().toInt();
//    int days = e->editVec[4]->text().toInt();

//    Database::changeWish(wish, goal, years, months, days, origWish, origGoal);

    Database::changeWish("Buy an iPhone 11", 10000, 1, 3, 0, "Buy an iPhone", 10000);
    close();
}

void Wish::wishLabelClicked()
{
     createNewWishVec();

     if (wishVec.size() <= 2) {
         setFixedHeight(MIN_HEIGHT + WISH_HEIGHT * wishVec.size());
     }

     ui->modifyButton->hide();
     ui->addWishes->hide();
     ui->saveButton->show();
}

void Wish::on_saveButton_clicked()
{
    qDebug() << "Save clicked";
}

void Wish::saveToBeModifiedWishList()
{
    QObject *wishList = sender();

    //disconnect one signal;
    int i, n = wishVec.size();
    for (i = 0; i < n; ++i) {
        if (wishList == wishVec[i]) {
            emit wishVec[i]->disconnectTextEditSignal();

            break;
        }
    }

    qDebug() << "To be modified";
}
