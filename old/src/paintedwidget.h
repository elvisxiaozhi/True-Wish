#ifndef PAINTEDWIDGET_H
#define PAINTEDWIDGET_H

#include <QWidget>
#include <QAction>
#include <QDebug>
#include <QPainter>
#include <QPaintEvent>
#include "customlabel.h"

using std::pair;

class PaintedWidget : public QWidget
{
    Q_OBJECT
public:
    explicit PaintedWidget(QWidget *parent = nullptr, const int width = 600);

protected:
    QAction *addAction(const QString &);
    void setOnHoverVec();
    void commonPaintEvent(bool redBgColor = false);
    void commonPressEvent(QMouseEvent *);
    QPixmap returnBinLabelPixmap(const QColor, const QPixmap);
    CustomLabel *createBinLabel();

private:
    const int WIDTH, GAP = 50;
    QList<QAction *> actionList;
    QVector<pair<bool, QRect> > onHoverVec;
    QRect onHoverRect;
    virtual void paintEvent(QPaintEvent *);
    void mouseMoveEvent(QMouseEvent *);
    virtual void mousePressEvent(QMouseEvent *);
    bool hoveredOnIcon();

signals:
    void actionChanged(int);
};

#endif // PAINTEDWIDGET_H
