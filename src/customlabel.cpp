#include "customlabel.h"
#include <QDebug>

CustomLabel::CustomLabel(QWidget *parent)
    :QLabel(parent)
{

}

CustomLabel::~CustomLabel()
{

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
