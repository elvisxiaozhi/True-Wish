#include "customlabel.h"
#include <QDebug>

CustomLabel::CustomLabel(QWidget *parent)
    :QLabel(parent)
{
    setStyleSheet("background-color: #11B850; border: 0px; padding: 15px 20px; font: 60px; color: white; border-radius: 3px;");
    setAlignment(Qt::AlignCenter);
    setFixedSize(250, 100);
}

CustomLabel::~CustomLabel()
{

}

void CustomLabel::mouseDoubleClickEvent(QMouseEvent *)
{
    emit doubleClicked();
}
