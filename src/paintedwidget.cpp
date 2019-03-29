#include "paintedwidget.h"
#include <windows.h>
#include <QWindow>
#include <QStyleOption>

PaintedWidget::PaintedWidget(QWidget *parent, const int width)
    : QWidget(parent), WIDTH(width)
{
    setMouseTracking(true);
    setWindowFlags(Qt::FramelessWindowHint);
}

QAction *PaintedWidget::addAction(const QString &text)
{
    QAction *action = new QAction(text, this);
    action->setCheckable(true);
    actionList.push_back(action);

    return action;
}

void PaintedWidget::setOnHoverVec()
{
    int n = actionList.size();
    for (int i = n; i > 0; --i) {
        onHoverVec.push_back(std::make_pair(false, QRect(WIDTH - i * GAP, 0, 50, 50)));
    }
}

void PaintedWidget::commonPaintFun()
{
    QPainter painter(this);

    //make custom widget able to set style sheet(change widget background color mainly)
    QStyleOption opt;
    opt.init(this);
    style()->drawPrimitive(QStyle::PE_Widget, &opt, &painter, this);

    painter.setFont(QFont("Times", 13));

    int n = actionList.size();
    for (auto action : actionList) {
        if (hoveredOnIcon() && WIDTH - n * GAP == onHoverRect.x()) {
            if(action->text() == "X") {
                painter.fillRect(onHoverRect, QColor(233, 75, 60));
                painter.setPen(Qt::white);
            }
            else {
                painter.fillRect(onHoverRect, QColor(35, 43, 62));
                painter.setPen(Qt::gray);
            }
        }
        else {
            painter.setPen(Qt::gray);
        }

        --n;
        QRect textRect(WIDTH - 33 - n * GAP, 10, GAP, GAP);
        painter.drawText(textRect, action->text());
    }
}

void PaintedWidget::paintEvent(QPaintEvent *)
{
    commonPaintFun();
}

void PaintedWidget::mouseMoveEvent(QMouseEvent *event)
{
    for (int i = 0; i < onHoverVec.size(); ++i) {
        if (onHoverVec[i].second.contains(QPoint(event->x(), event->y()))) {
            if (event->y() >= 5 && event->x() <= WIDTH - 5) { //this if statement here is to prevent the hover effect stay issue
                onHoverVec[i].first = true;
            }
            else {
                onHoverVec[i].first = false;
            }
        }
        else {
            onHoverVec[i].first = false;
        }
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

    int n = onHoverVec.size();
    for (int i = 0; i < n; ++i) {
        if (onHoverVec[i].second.contains(QPoint(event->x(), event->y()))) {
            int index = n - (WIDTH - onHoverVec[i].second.x()) / GAP;
            emit actionChanged(index);
            qDebug() << index;
        }
    }

    update();
}

bool PaintedWidget::hoveredOnIcon()
{
    for (int i = 0; i < onHoverVec.size(); ++i) {
        if (onHoverVec[i].first == true) {
            onHoverRect = onHoverVec[i].second;
            return true;
        }
    }

    return false;
}














