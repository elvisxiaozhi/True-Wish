#include "paintedwidget.h"
#include <QPainter>
#include <QPaintEvent>
#include <windows.h>
#include <QWindow>

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
    actionList.push_back(action);

    return action;
}

void PaintedWidget::setOnHoverMap()
{
    int n = actionList.size();
    for (int i = n; i > 0; --i) {
        onHoverMap.insert(std::make_pair(WIDTH - i * GAP, WIDTH - (i - 1) * GAP), QRect(WIDTH - i * GAP, 0, 50, 50));
    }
}

void PaintedWidget::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);
    painter.setFont(QFont("Times", 13));

    int n = actionList.size();
    for (auto action : actionList) {
//        if (onHoverRec)
//        if (onHover) {
//            if (onHoverRec == QRect(550, 0, 50, 50)) { //when hover on the 'X'
//                painter.fillRect(onHoverRec, QColor(233, 75, 60));
//                painter.setPen(Qt::white);
//            }
//            else {
//                painter.fillRect(onHoverRec, Qt::yellow);
////                painter.fillRect(onHoverRec, QColor(35, 43, 62));
////                painter.setPen(Qt::white);
//            }
//        }
//        else {
//            painter.setPen(Qt::gray);
//        }

        --n;
        QRect textRect(WIDTH - 30 - (n * GAP), 10, event->rect().width(), event->rect().height());
        painter.drawText(textRect, action->text());
    }
}

void PaintedWidget::mouseMoveEvent(QMouseEvent *event)
{
    if (event->y() <= GAP) {
        int n = actionList.size();
        if (event->x() >= WIDTH - n * 50 && event->x() <= WIDTH) {
            onHover = true;
            for (auto value : onHoverMap.values()) {
                if (event->x() >= onHoverMap.key(value).first && event->x() <= onHoverMap.key(value).second) {
                    onHoverRec = value;
                    break;
                }
            }
        }
    }
    else {
        onHover = false;
    }

    update();
}

void PaintedWidget::mousePressEvent(QMouseEvent *event)
{
    //use native windows api to move window
    if (event->buttons().testFlag(Qt::LeftButton))
    {
        HWND hWnd = ::GetAncestor((HWND)(window()->windowHandle()->winId()), GA_ROOT);
        POINT pt;
        ::GetCursorPos(&pt);
        ::ReleaseCapture();
        ::SendMessage(hWnd, WM_NCLBUTTONDOWN, HTCAPTION, POINTTOPOINTS(pt));
    }

    update();
}














