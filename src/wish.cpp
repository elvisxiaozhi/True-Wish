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

    createNewWishList();

    wishVec.first()->isBinLabelHidden(false); //default wish vec can not be deleted
    createWishLabel();

    connect(this, &Wish::actionChanged, [this](){ closeWindow(); });

    setFixedHeight(MIN_HEIGHT + WISH_HEIGHT * wishVec.size());
}

Wish::~Wish()
{
    delete ui;
}

void Wish::setWishInfo(int index, QString wish, int goal, int years, int months, int days)
{
    WishList *w = wishVec[index];
    w->editVec[0]->setText(wish);
    w->editVec[1]->setText(QString::number(goal));
    w->editVec[2]->setText(QString::number(years));
    w->editVec[3]->setText(QString::number(months));
    w->editVec[4]->setText(QString::number(days));

    origWish = wish; //change later
    origGoal = goal; //change later

    wishListValues.push_back(make_tuple(wish, goal, years, months, days));
}

void Wish::setAddWishWindow()
{
    ui->title->setText("Add Wishes");
    ui->addWishes->show();
    ui->modifyButton->hide();
    ui->saveButton->hide();
    if (wishVec.empty() == false) {
        wishVec.first()->isBinLabelHidden(false);
    }
}

void Wish::setChangeWishWindow()
{
    ui->title->setText("Change Wishes");
    ui->modifyButton->show();
    ui->addWishes->hide();
    ui->saveButton->hide();
    wishVec.first()->isBinLabelHidden(true);

    setFixedHeight(MIN_HEIGHT + WISH_HEIGHT * wishVec.size());
}

int Wish::returnWishVecSize()
{
    return wishVec.size();
}

void Wish::createMoreWishLists(int max)
{
    int i, n = max - wishVec.size();
    for (i = 0; i < n; ++i) {
        createNewWishList();
    }
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

//after click "X" or close button, some changes need to be rest
void Wish::closeWindow()
{
    for (auto wishList : wishVec) {
        wishList->clearFocus(); //clear focus

        //IMPORTANT: wishVec.size() must > 1, why? see setAddWishWindow function
        if (wishVec.size() > 1) {
            //remove empty wish list except the first one
            if (isWishListEmpty(wishList)) {
                wishList->emitBinLabelClickedSignal();
            }
        //delete later
//        emit wishList->lineEditTextEdited(false); //reconnect wish list signal
        }

    }
    wishListValues.clear(); //clear wishListValues, each time when window reopen, it will be set to new values

    close(); //close must be called after wish list is removed
}

QVector<tuple<QString, int, int, int, int> > Wish::getWishes()
{
    QVector<tuple<QString, int, int, int, int> > res;

    int i, n = wishVec.size();
    for (i = 0; i < n; ++i) {
        res.push_back(make_tuple(wishVec[i]->editVec[0]->text(), wishVec[i]->editVec[1]->text().toInt(), wishVec[i]->editVec[2]->text().toInt(),
                wishVec[i]->editVec[3]->text().toInt(), wishVec[i]->editVec[4]->text().toInt()));
    }

    return res;
}

void Wish::printVec(QVector<tuple<QString, int, int, int, int> > res)
{
    int i;
    for (i = 0; i < res.size(); ++i) {
        qDebug() << get<0>(res[i]) << get<1>(res[i])
                 << get<2>(res[i]) << get<3>(res[i]) << get<4>(res[i]);
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
            Database::deleteWish(wishVec[i]->editVec[0]->text(), wishVec[i]->editVec[1]->text().toInt());
            emit wishDeleted();

            if (i != 0) {
                delete wishVec[i]; //delete first
                delete frameVec[i];
                wishVec.erase(wishVec.begin() + i); //then erase index from vector to prevent out of index issue in MousePressEvent()
                frameVec.erase(frameVec.begin() + i);
            }
            else {
                //clear the first wish list all texts and reset the first wish list
                wishVec[i]->clearText();
                wishVec[i]->clearFocus();
            }

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
    closeWindow();
}

void Wish::createNewWishList()
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
        }

        resetLineEdits();
        closeWindow();

        emit wishAdded();
    }
}

void Wish::on_modifyButton_clicked()
{
    QVector<tuple<QString, int, int, int, int> > newWishes = getWishes();
    int i, n = wishListValues.size();
    if (n > newWishes.size()) {
        n = newWishes.size();
    }
    for (i = 0; i < n; ++i) {
        if (wishListValues[i] != newWishes[i]) {
            Database::changeWish(get<0>(newWishes[i]), get<1>(newWishes[i]), get<2>(newWishes[i]), get<3>(newWishes[i]), get<4>(newWishes[i]),
                    get<0>(wishListValues[i]), get<1>(wishListValues[i]));
        }
    }

    closeWindow();

    emit wishModified();
}

void Wish::wishLabelClicked()
{
     createNewWishList();

     if (wishVec.size() <= 2) {
         setFixedHeight(MIN_HEIGHT + WISH_HEIGHT * wishVec.size());
     }

     ui->modifyButton->hide();
     ui->addWishes->hide();
     ui->saveButton->show();
}

void Wish::on_saveButton_clicked()
{
    if (!allFilled()) {
        changeUnderLineToRed();
    }
    else {
        QVector<tuple<QString, int, int, int, int> > newWishes = getWishes();
        printVec(newWishes);

        int i, n = wishListValues.size();
        for (i = 0; i < n; ++i) {
            if (wishListValues[i] != newWishes[i]) {
                Database::changeWish(get<0>(newWishes[i]), get<1>(newWishes[i]), get<2>(newWishes[i]), get<3>(newWishes[i]), get<4>(newWishes[i]),
                        get<0>(wishListValues[i]), get<1>(wishListValues[i]));
            }
        }

        int j = n;
        n = newWishes.size();
        for (i = j; i < n; ++i) {
            Database::addWish(QDate::currentDate().toString("yyyy-MM-dd"), get<0>(newWishes[i]), get<1>(newWishes[i]), get<2>(newWishes[i]), get<3>(newWishes[i]), get<4>(newWishes[i]));
        }

        closeWindow();

        emit newWishSaved();
    }
}

void Wish::saveToBeModifiedWishList(bool /*isEdited*/)
{
//    qDebug() << isEdited;

//    qDebug() << "To be modified";
}
