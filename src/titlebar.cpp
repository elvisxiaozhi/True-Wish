#include "titlebar.h"
#include <QPaintEvent>
#include <QStyleOption>
#include <QPainter>
#include <windows.h>
#include <QWindow>
#include <QDebug>

const int TitleBar::POS_X = 1155;

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
    int posX = POS_X;
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

     painter.setFont(QFont("Times", 13));

     int posX = POS_X + 15; //+15 to move '-' and 'X' to the center
     for(auto action : actList) {
         if(action == hoveredAct) {
             QPen pen;
             pen.setWidth(5);
             pen.setBrush(QColor(255, 0, 0));
             painter.setPen(pen);

             //set on hover background color
             if(action->text() == "—") {
                 painter.fillRect(QRect(POS_X, 0, 50, 50), QColor(35, 43, 62));
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

    update();
}

void TitleBar::mouseMoveEvent(QMouseEvent *event)
{
    if(event->x() < 1250 && event->x() >= POS_X) {
        hoveredOnNotify = true;
    }
    else {
        hoveredOnNotify = false;
    }

    QAction *action = actionAt(event->pos());
    hoveredAct = action;

    update();
}
