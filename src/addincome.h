#ifndef ADDINCOME_H
#define ADDINCOME_H

#include <QWidget>
#include <QAction>
#include <QFrame>

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
    QFrame *line;

    QAction *addAction(const QString &);
    QAction *actionAt(const QPoint &);
    void createLine();

protected:
    void paintEvent(QPaintEvent *);
    void mouseMoveEvent(QMouseEvent *);
    void mousePressEvent(QMouseEvent *);
private slots:
    void on_closeButton_clicked();
};

#endif // ADDINCOME_H
