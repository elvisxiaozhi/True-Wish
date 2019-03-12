#ifndef INCOME_H
#define INCOME_H

#include "customwidget.h"
#include <QDate>
#include "customlineedit.h"
#include "database.h"
#include "customlabel.h"

class Income : public CustomWidget
{
    Q_OBJECT

public:
    explicit Income(CustomWidget *parent = 0);
    ~Income();
    static int income;
    static QString incomeAddedDate;

    void setAddIncomeWindow();
    void setChangeIncomeWindow();
    static void updateIncomeInfo();

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
