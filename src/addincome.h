#ifndef ADDINCOME_H
#define ADDINCOME_H

#include <QWidget>
#include <QAction>
#include <QDate>
#include "customlineedit.h"
#include "database.h"
#include "customlabel.h"

namespace Ui {
class AddIncome;
}

class AddIncome : public QWidget
{
    Q_OBJECT

public:
    explicit AddIncome(QWidget *parent = 0);
    ~AddIncome();
    static int income;
    static QString incomeAddedDate;

    void changeIncome();

private:
    Ui::AddIncome *ui;

    QAction *closetAction;
    bool onHover;
    CustomLineEdit *lineEdit;
    CustomLabel *binLabel;

    QAction *addAction(const QString &);
    QAction *actionAt(const QPoint &);
    void createLineEdit();
    void createBinLabel();
    void setBinLabelPixmap(QColor);
    void createLine();

protected:
    void paintEvent(QPaintEvent *);
    void mouseMoveEvent(QMouseEvent *);
    void mousePressEvent(QMouseEvent *);

private slots:
    void on_closeButton_clicked();
    void on_addButton_clicked();
    void on_modifyButton_clicked();
};

#endif // ADDINCOME_H
