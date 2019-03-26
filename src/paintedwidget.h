#ifndef PAINTEDWIDGET_H
#define PAINTEDWIDGET_H

#include <QWidget>
#include <QAction>
#include <QDebug>

class PaintedWidget : public QWidget
{
    Q_OBJECT
public:
    explicit PaintedWidget(QWidget *parent = nullptr);

protected:
    void setWidth(const int width);

    QAction *closeAction;

    QAction *addAction(const QString &);

private:
    const int WIDTH = 600;
    bool onHover;
    void paintEvent(QPaintEvent *);

};

#endif // PAINTEDWIDGET_H
