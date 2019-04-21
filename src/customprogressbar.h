#ifndef CUSTOMPROGRESSBAR_H
#define CUSTOMPROGRESSBAR_H

#include <QProgressBar>

class CustomProgressBar : public QProgressBar
{
    Q_OBJECT
public:
    explicit CustomProgressBar(QWidget *parent = nullptr);
    void setBarValues(int, int);

private:
    void mouseMoveEvent(QMouseEvent *);
    static QString styleSheet;
};

#endif // CUSTOMPROGRESSBAR_H
