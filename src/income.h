#ifndef INCOME_H
#define INCOME_H

#include "inandexwidget.h"

class Income : public InAndExWidget
{
    Q_OBJECT

public:
    explicit Income(InAndExWidget *parent = 0);
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
