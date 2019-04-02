#include "paintedwidget.h"
#include <windows.h>
#include <QWindow>
#include <QStyleOption>
#include <QBitmap>

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

void PaintedWidget::commonPaintEvent(bool redBgColor)
{
    QPainter painter(this);
    painter.setFont(QFont("Times", 13));

    if (redBgColor) {
        //make custom widget able to set style sheet(change widget background color mainly)
        QStyleOption opt;
        opt.init(this);
        style()->drawPrimitive(QStyle::PE_Widget, &opt, &painter, this);
    }

    int n = actionList.size();
    for (auto action : actionList) {
        if (hoveredOnIcon() && WIDTH - n * GAP == onHoverRect.x()) {
            if(action->text() == "X") {
                if (redBgColor) {
                    painter.fillRect(onHoverRect, QColor(233, 75, 60));
                }
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

void PaintedWidget::commonPressEvent(QMouseEvent *event)
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
        }
    }

    update();
}

void PaintedWidget::paintEvent(QPaintEvent *)
{
    commonPaintEvent();
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
    commonPressEvent(event);
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

QPixmap PaintedWidget::returnBinLabelPixmap(const QColor color, const QPixmap px)
{
    QPixmap pixmap(px.size());
    pixmap.fill(color);
    pixmap.setMask(px.createMaskFromColor(Qt::transparent));

    return pixmap;
}

CustomLabel *PaintedWidget::createBinLabel()
{
    CustomLabel *binLabel = new CustomLabel(this);
    binLabel->setFixedSize(30, 30);

    connect(binLabel, &CustomLabel::entered, [this, binLabel](){ binLabel->setPixmap(returnBinLabelPixmap(QColor(255, 255, 255), QPixmap(":/icons/recycle bin.png"))); });
    connect(binLabel, &CustomLabel::left, [this, binLabel](){ binLabel->setPixmap(QPixmap()); });

    return binLabel;
}














