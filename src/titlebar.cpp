#include "titlebar.h"
#include <QPaintEvent>
#include <QStyleOption>
#include <QPainter>
#include <windows.h>
#include <QWindow>
#include <QDebug>

TitleBar::TitleBar(QWidget *parent) : QWidget(parent), checkedAct(nullptr), hoveredAct(nullptr)
{
    setMouseTracking(true);

    addAction("—", QIcon(""));
    addAction("X", QIcon(""));

    setStyleSheet("QWidget { background-color: #2E364D; }");
    setFixedSize(1250, 50);
}

//draw '-' and 'X' on title bar
QAction *TitleBar::addAction(const QString &text, const QIcon &icon)
{
    QAction *action = new QAction(icon, text, this);
    action->setCheckable(true);
    actList.push_back(action);
    return action;
}

QAction *TitleBar::actionAt(const QPoint &point)
{
    int posX = 1155;
    for(auto action : actList) {
        QRect actRect(posX, 10, 35, 35); //35 or whatever less than its width(50) and height(50), or sometimes the hover effect will stay
        if(actRect.contains(point))
            return action;

        posX += 50;
    }

    return nullptr;
}

void TitleBar::paintEvent(QPaintEvent *event)
{
     //make custom widget able to set style sheet(change widget background color mainly)
     QStyleOption opt;
     opt.init(this);
     QPainter painter(this);
     style()->drawPrimitive(QStyle::PE_Widget, &opt, &painter, this);

     QFont font("Times", 13);
     painter.setFont(font);

     int posX = 1155 + 15; //+15 to move '-' and 'X' to the center
     for(auto action : actList) {
         if(action == hoveredAct) {
             QPen pen;
             pen.setWidth(5);
             pen.setBrush(QColor(255, 0, 0));
             painter.setPen(pen);

             //set on hover background color
             if(action->text() == "—") {
                 painter.fillRect(QRect(1155, 0, 50, 50), QColor(35, 43, 62));
                 painter.setPen(Qt::gray);
             }
             else if(action->text() == "X") {
                 painter.fillRect(QRect(1203, 0, 50, 50), QColor(233, 75, 60));
                 painter.setPen(Qt::white);
             }
         }
         else {
             //set icon text color to gray when unhover
             painter.setPen(Qt::gray);
         }

         QRect textRect(posX, 10, event->rect().width(), event->rect().height());
         painter.drawText(textRect, action->text());

         posX += 50;
     }

//     if(hoveredOnNotify) {
//         painter.fillRect(QRect(915, 0, 45, 45), QColor(0,255,255)); //set background color
//     }
//     //paint icon
//     QIcon icon(":/icons/notification.png");
//     QRect iconRect(915 + 10, 10, 25, 25); //plus 12, so the icon can align center
//     icon.paint(&painter, iconRect);
}

void TitleBar::mousePressEvent(QMouseEvent *event)
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

    QAction *action = actionAt(event->pos());
    checkedAct = action;
    if(checkedAct != nullptr) {
        int index = std::find(actList.begin(), actList.end(), checkedAct) - actList.begin();
        emit actionChanged(index);
    }
    //    update(); //update must be in the last, or the window will suddently move to another place
}

void TitleBar::mouseMoveEvent(QMouseEvent *event)
{
    if(event->x() < 1250 && event->x() >= 1155) {
        hoveredOnNotify = true;
    }
    else {
        hoveredOnNotify = false;
    }

    QAction *action = actionAt(event->pos());
    hoveredAct = action;
//    update(); //update must be in the last, or the window will suddently move to another place
}
