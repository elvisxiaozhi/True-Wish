#ifndef CUSTOMLABEL_H
#define CUSTOMLABEL_H

#include <QLabel>

class CustomLabel : public QLabel
{
    Q_OBJECT
public:
    CustomLabel(QWidget *parent = nullptr);
    ~CustomLabel();

    void setInAndExAttr();

protected:
    void mousePressEvent(QMouseEvent *);
    void mouseDoubleClickEvent(QMouseEvent *);
    void enterEvent(QEvent *);
    void leaveEvent(QEvent *);

signals:
    void clicked();
    void doubleClicked();
    void entered();
    void left();
};

#endif // CUSTOMLABEL_H
