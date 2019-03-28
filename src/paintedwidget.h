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
    explicit PaintedWidget(QWidget *parent = nullptr, const int width = 600);

protected:
    QAction *addAction(const QString &);
    void setOnHoverVec();

private:
    const int WIDTH, GAP = 50;
    QList<QAction *> actionList;
    QVector<pair<bool, QRect> > onHoverVec;
    QRect onHoverRect;
    void paintEvent(QPaintEvent *);
    void mouseMoveEvent(QMouseEvent *);
    void mousePressEvent(QMouseEvent *);
    bool hoveredOnIcon();

signals:
    void actionChanged(int);
};

#endif // PAINTEDWIDGET_H
