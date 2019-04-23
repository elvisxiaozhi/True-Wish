#include "wishlist.h"
#include "ui_wishlist.h"

WishList::WishList(PaintedWidget *parent) :
    PaintedWidget(parent),
    ui(new Ui::WishList)
{
    ui->setupUi(this);

    createNewWishEdit("What are you wishing for?", ui->wishLayout);
    createNewWishEdit("What is your financial goal?", ui->goalLayout);
    createTimeEdit();
    setBinLable();

    editVec[0]->setValidator(nullptr);

    for (auto e : editVec) {
        connect(e, &CustomLineEdit::changeUnderLineToRed, this, &WishList::changeUnderLineToRed);
    }

    setStyleSheet("QWidget { background: #414B66; border: 1px solid gray; }");

    /*It's not necessary to set fixed height in this class, just set fixed height for QFrame widget in Wish class*/
}

WishList::~WishList()
{
    delete ui;
}

void WishList::createTimeEdit()
{
    QLabel *timeLabel = new QLabel(this);
    timeLabel->setText("How long will it take to achieve your financial goal?");
    timeLabel->setStyleSheet("font: 20px; color: #BFC6D6; border: none; padding: 0px 0px 0px 1px;");

    QHBoxLayout *hLayout = new QHBoxLayout;
    createNewWishEdit("Year(s)", hLayout, 160);
    createNewWishEdit("Month(s)", hLayout, 160);
    createNewWishEdit("Day(s)", hLayout, 160);

    QVBoxLayout *vLayout = new QVBoxLayout;
    vLayout->addWidget(timeLabel);
    vLayout->addLayout(hLayout);

    ui->timeLayout->addLayout(vLayout);
}

void WishList::setBinLable()
{
    binLabel = createBinLabel();

    ui->binWidget->setFixedSize(30, 30);
    ui->binLayout->addWidget(binLabel);

    connect(binLabel, &CustomLabel::clicked, [this](){ emit deleteWishList(); });
}

void WishList::changeUnderLineToRed()
{
    QObject *lineEdit = sender();
    for (auto e : editVec) {
        if (e == lineEdit) {
            e->setStyleSheet(CustomLineEdit::styleString.arg("red"));
        }
    }
}

void WishList::clearFocus()
{
    for (auto e : editVec) {
        e->clearFocus();
        emit e->isFocused(false);
    }
}

void WishList::isBinLabelShown(bool state)
{
    if (state)
        binLabel->show();
    else
        binLabel->hide();
}

void WishList::createNewWishEdit(QString text, QLayout *layout, int width)
{
    CustomLineEdit *lineEdit = new CustomLineEdit(this);
    lineEdit->setWishAttr(text, width);
    layout->addWidget(lineEdit);

    editVec.push_back(lineEdit);
}
