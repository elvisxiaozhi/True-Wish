#include "titlebar.h"

TitleBar::TitleBar(PaintedWidget *parent, int width) : PaintedWidget(parent, width)
{
    addAction("—");
    addAction("X");
    setOnHoverVec();
    setFixedSize(1250, 50);
    setStyleSheet("background-color: #2E364D");
}

void TitleBar::paintEvent(QPaintEvent *event)
{
    commonPaintEvent(true);

    QPainter painter(this);
    //paint icon
    QIcon icon(":/icons/star.png");
    QRect iconRect(20, 5, 40, 40);
    icon.paint(&painter, iconRect);

    //paint name
    QRect textRect(65, 10, event->rect().width(), event->rect().height());
    painter.setPen(QPen(Qt::white));
    painter.setFont(QFont("times", 11));
    painter.drawText(textRect, "True Wish");
}
