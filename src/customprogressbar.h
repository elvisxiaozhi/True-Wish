#ifndef CUSTOMPROGRESSBAR_H
#define CUSTOMPROGRESSBAR_H

#include <QProgressBar>

class CustomProgressBar : public QProgressBar
{
    Q_OBJECT
public:
    explicit CustomProgressBar(QWidget *parent = nullptr);

private:
    void mouseMoveEvent(QMouseEvent *);
};

#endif // CUSTOMPROGRESSBAR_H
