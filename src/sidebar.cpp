#include "sidebar.h"
#include <QPaintEvent>
#include <QMouseEvent>
#include <QPainter>
#include <QDebug>
#include <QIcon>

const int Sidebar::POS_Y = 135;

Sidebar::Sidebar(QWidget *parent) : QWidget(parent), hoveredAct(nullptr)
{
    setMouseTracking(true);

    addAction(tr("Overview"), QIcon(":/icons/home_24px.png"));
    addAction(tr("Protection"), QIcon(":/icons/dashboard_24px.png"));
    addAction(tr("Users"), QIcon(":/icons/users_24px.png"));
    addAction(tr("Settings"), QIcon(":/icons/settings_24px.png"));

    checkedAct = actList[0];
    checkedIndex = 0;

    setFixedSize(160, 800);
}

QAction *Sidebar::addAction(const QString &text, const QIcon &icon)
{
    QAction *action = new QAction(icon, text, this);
    action->setCheckable(true);
    actList.push_back(action);
    return action;
}

QAction *Sidebar::actionAt(const QPoint &point)
{
    int posY = 0;
    for(auto action : actList) {
        QRect actRect(0, 0, 160, posY);
        if(actRect.contains(point))
            return action;

        posY += POS_Y;
    }
    return nullptr;
}

void Sidebar::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);
    painter.fillRect(rect(), QColor(46, 62, 77)); //set background color

    int posY = POS_Y;
    for (auto action : actList) {
        painter.setPen(QPen(QColor(46, 41, 41)));
        painter.drawLine(0, posY, 160, posY);

        if (action == checkedAct) {
            painter.fillRect(QRect(0, checkedIndex * POS_Y, 160, posY - checkedIndex * POS_Y), QColor(101, 51, 172));
        }
        if (action == hoveredAct && checkedIndex != hoveredIndex) {
            painter.fillRect(QRect(0, hoveredIndex * POS_Y, 160, posY - hoveredIndex * POS_Y), QColor(35, 43, 62));
        }

//        QIcon icon(action->icon());
//        QRect iconRect(10, posY, 30, 30);
//        icon.paint(&painter, iconRect);

        QRect textRect(50, posY - 50, event->rect().width(), event->rect().height());
        painter.setPen(QPen(Qt::white));
        painter.setFont(QFont("times", 10));
        painter.drawText(textRect, action->text());

        posY += POS_Y;
    }
}

void Sidebar::mousePressEvent(QMouseEvent *event)
{
    QAction *action = actionAt(event->pos());

    checkedIndex = std::find(actList.begin(), actList.end(), action) - actList.begin() - 1;
    checkedAct = actList[checkedIndex];
    emit actionChanged(checkedIndex);

    update();
}

void Sidebar::mouseMoveEvent(QMouseEvent *event)
{
    QAction *action = actionAt(event->pos());

    hoveredIndex = std::find(actList.begin(), actList.end(), action) - actList.begin() - 1;
    hoveredAct = actList[hoveredIndex];

    update();
}
