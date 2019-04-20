#include "wishdetail.h"
#include <QVBoxLayout>
#include <QDebug>

WishDetail::WishDetail(QWidget *parent) :
    QWidget(parent)
{
    createWishLabel();

    progressBar = new CustomProgressBar(this);

    QVBoxLayout *vLayout = new QVBoxLayout(this);
    vLayout->addWidget(label);
    vLayout->addWidget(progressBar);
}

void WishDetail::setWishLableText(QString wish)
{
    label->setText(wish);
}

void WishDetail::createWishLabel()
{
    label = new CustomLabel(this);
    label->setStyleSheet("background-color: #11B850; border: 0px; padding: 15px 20px; font: 20px; color: white; border-radius: 3px;");
    label->setTextFormat(Qt::RichText);
}
