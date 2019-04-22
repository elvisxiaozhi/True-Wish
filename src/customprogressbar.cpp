#include "customprogressbar.h"
#include <QToolTip>
#include <QMouseEvent>
#include <QDebug>

QString CustomProgressBar::styleSheet = QString("QWidget { background-color: %1; }"
                                                "QProgressBar { color: #353F5A; font: 16px; border-radius: 5px; text-align: center; border: 2px solid gray; }"
                                                "QProgressBar::chunk { background-color: %2; width: 20px; }");

CustomProgressBar::CustomProgressBar(QWidget *parent) : QProgressBar(parent)
{
    setMouseTracking(true);

    setStyleSheet(styleSheet.arg("white").arg("#11B850"));
}

void CustomProgressBar::setBarValues(int value, int max)
{
    setValue(value);
    setMaximum(max);
    int percentage = (1 - (float)value / (float)max) * 100;
    setFormat(QString::number(percentage) + "%");

    setStyleSheet(styleSheet.arg("#11B850").arg("white")); //to make the bar look like in a backwards position
}

void CustomProgressBar::mouseMoveEvent(QMouseEvent *event)
{
    emit updateToolTip();

    QToolTip::showText(mapToGlobal(event->pos()), toolTip);

    update();
}
