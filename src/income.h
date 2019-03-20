#ifndef INCOME_H
#define INCOME_H

#include "customwidget.h"

class Income : public CustomWidget
{
    Q_OBJECT

public:
    explicit Income(CustomWidget *parent = 0);
    ~Income();

    void setAddIncomeWindow(const QString);
    void setChangeIncomeWindow(const QString);
    static tuple<QString, int> updateIncomeInfo(QString);

private:
    static int income;
    static QString incomeAddedDate;
    CustomLabel *binLabel;

    void setIncomeButtons();

signals:
    void incomeAdded();
    void incomeChanged();
    void incomeDeleted();

private slots:
    void addIncome();
    void changeIncome();
    void deleteIncome();
};

#endif // INCOME_H
