#include "customlabel.h"
#include <QDebug>

CustomLabel::CustomLabel(QWidget *parent)
    :QLabel(parent)
{
    setAlignment(Qt::AlignCenter);
}

CustomLabel::~CustomLabel()
{

}

void CustomLabel::setInAndExAttr()
{
    setStyleSheet("background-color: #11B850; border: 0px; padding: 15px 20px; font: 60px; color: white; border-radius: 3px;");
    setFixedSize(250, 100);

    hide();
}

void CustomLabel::mousePressEvent(QMouseEvent *)
{
    emit clicked();
}

void CustomLabel::mouseDoubleClickEvent(QMouseEvent *)
{
    emit doubleClicked();
}

void CustomLabel::enterEvent(QEvent *)
{
    emit entered();
}

void CustomLabel::leaveEvent(QEvent *)
{
    emit left();
}
