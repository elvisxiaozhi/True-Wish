#ifndef ADDINCOME_H
#define ADDINCOME_H

#include <QWidget>
#include <QAction>

namespace Ui {
class AddIncome;
}

class AddIncome : public QWidget
{
    Q_OBJECT

public:
    explicit AddIncome(QWidget *parent = 0);
    ~AddIncome();

private:
    Ui::AddIncome *ui;

    QAction *closetAction;
    bool onHover;

    QAction *addAction(const QString &);
    QAction *actionAt(const QPoint &);

protected:
    void paintEvent(QPaintEvent *);
    void mouseMoveEvent(QMouseEvent *);
    void mousePressEvent(QMouseEvent *);
};

#endif // ADDINCOME_H
