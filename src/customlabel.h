#ifndef CUSTOMLABEL_H
#define CUSTOMLABEL_H

#include <QLabel>

class CustomLabel : public QLabel
{
    Q_OBJECT
public:
    CustomLabel(QWidget *parent = nullptr);
    ~CustomLabel();

protected:
    void mouseDoubleClickEvent(QMouseEvent *);

signals:
    void doubleClicked();
};

#endif // CUSTOMLABEL_H
