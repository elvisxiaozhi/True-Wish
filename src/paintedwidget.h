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
    void setOnHoverVec();

private:
    const int WIDTH = 600, GAP = 50;
    QList<QAction *> actionList;
    QVector<pair<bool, QRect> > onHoverVec;
    QRect onHoverRect;
    void paintEvent(QPaintEvent *);
    void mouseMoveEvent(QMouseEvent *);
    void mousePressEvent(QMouseEvent *);
    bool hoveredOnIcon();
};

#endif // PAINTEDWIDGET_H
