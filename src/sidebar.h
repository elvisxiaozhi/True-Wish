#ifndef SIDEBAR_H
#define SIDEBAR_H

#include <QWidget>
#include <QAction>

class Sidebar : public QWidget
{
    Q_OBJECT
public:
    explicit Sidebar(QWidget *parent = nullptr);

private:
    int checkedIndex;
    int hoveredIndex;
    static const int POS_Y;
    QList<QAction *> actList;
    QAction *checkedAct;
    QAction *hoveredAct;

    QAction *addAction(const QString &, const QIcon &);
    QAction *actionAt(const QPoint &);

protected:
    void paintEvent(QPaintEvent *);
    void mousePressEvent(QMouseEvent *);
    void mouseMoveEvent(QMouseEvent *);

signals:
    void actionChanged(int);
};

#endif // SIDEBAR_H
