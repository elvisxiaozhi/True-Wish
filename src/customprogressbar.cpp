#include "customprogressbar.h"
#include <QToolTip>
#include <QMouseEvent>
#include <QDebug>

CustomProgressBar::CustomProgressBar(QWidget *parent) : QProgressBar(parent)
{
    setMouseTracking(true);
    setValue(30);
}

void CustomProgressBar::mouseMoveEvent(QMouseEvent *event)
{
    QToolTip::showText(mapToGlobal(event->pos()), "Tool tip");

    update();
}
