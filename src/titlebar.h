#ifndef TITLEBAR_H
#define TITLEBAR_H

#include <QWidget>
#include <QAction>

class TitleBar : public QWidget
{
    Q_OBJECT
public:
    explicit TitleBar(QWidget *parent = nullptr);

private:
    QList<QAction *> actList;
    QAction *checkedAct;
    QAction *hoveredAct;
    bool hoveredOnNotify;
    static const int POS_X;

    QAction *addAction(const QString &, const QIcon &);
    QAction *actionAt(const QPoint &);

protected:
    void paintEvent(QPaintEvent *);
    void mousePressEvent(QMouseEvent *);
    void mouseMoveEvent(QMouseEvent *);

signals:
    void actionChanged(int);
};

#endif // TITLEBAR_H
