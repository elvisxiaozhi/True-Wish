#include "paintedwidget.h"
#include <QPainter>
#include <QPaintEvent>

PaintedWidget::PaintedWidget(QWidget *parent)
    : QWidget(parent)
{
    setMouseTracking(true);
    setWindowFlags(Qt::FramelessWindowHint);
}

void PaintedWidget::setWidth(const int width)
{
    int *ptr = const_cast<int *>(&WIDTH);
    *ptr = width;
}

QAction *PaintedWidget::addAction(const QString &text)
{
    QAction *action = new QAction(text, this);
    action->setCheckable(true);

    return action;
}

void PaintedWidget::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);
    painter.setFont(QFont("Times", 13));

    QRect textRect(WIDTH, 10, event->rect().width(), event->rect().height());
//    painter.setPen(pen);
    painter.drawText(textRect, closeAction->text());
}
