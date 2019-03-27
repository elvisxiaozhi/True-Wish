#ifndef PAINTEDWIDGET_H
#define PAINTEDWIDGET_H

#include <QWidget>
#include <QAction>
#include <QDebug>

using std::pair;

class PaintedWidget : public QWidget
{
    Q_OBJECT
public:
    explicit PaintedWidget(QWidget *parent = nullptr);

protected:
    void setWidth(const int width);

    QAction *addAction(const QString &);
    void setOnHoverMap();

private:
    const int WIDTH = 600, GAP = 50;
    QList<QAction *> actionList;
    QMap<pair<int, int>, QRect> onHoverMap;
    bool onHover = false;
    QRect onHoverRec;
    void paintEvent(QPaintEvent *);
    void mouseMoveEvent(QMouseEvent *);
    void mousePressEvent(QMouseEvent *);

};

#endif // PAINTEDWIDGET_H
