#ifndef INCOME_H
#define INCOME_H

#include <QWidget>
#include <QAction>
#include <QDate>
#include "customlineedit.h"
#include "database.h"
#include "customlabel.h"

namespace Ui {
class InAndEx;
}

class Income : public QWidget
{
    Q_OBJECT

public:
    explicit Income(QWidget *parent = 0);
    ~Income();
    static int income;
    static QString incomeAddedDate;

    void changeIncome();
    void addIncome();
    static void updateIncomeInfo();

private:
    Ui::InAndEx *ui;

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

signals:
    void incomeAdded();
    void incomeChanged();
    void incomeDeleted();

private slots:
    void on_closeButton_clicked();
    void on_addButton_clicked();
    void on_modifyButton_clicked();
    void deleteIncome();
};

#endif // INCOME_H
