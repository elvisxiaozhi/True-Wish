#ifndef CUSTOMPROGRESSBAR_H
#define CUSTOMPROGRESSBAR_H

#include <QProgressBar>

class CustomProgressBar : public QProgressBar
{
    Q_OBJECT
public:
    explicit CustomProgressBar(QWidget *parent = nullptr);
    void setBarValues(int, int);
    QString toolTip;

private:
    void mouseMoveEvent(QMouseEvent *);
    static QString styleSheet;

signals:
    void updateToolTip();
};

#endif // CUSTOMPROGRESSBAR_H
