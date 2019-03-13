#ifndef EXPENDITURE_H
#define EXPENDITURE_H

#include "customwidget.h"

class Expenditure : public CustomWidget
{
    Q_OBJECT
public:
    explicit Expenditure(CustomWidget *parent = nullptr);
    ~Expenditure();

    void setAddExpenditureWindow();
    void setChangeExpenditureWindow();
    static tuple<QString, int> updateExpenditureInfo();

private:
    static int expenditure;
    static QString expenditureAddedDate;
    CustomLabel *binLabel;

    void setExpenditureButtons();

signals:
    void expenditureAdded();
    void expenditureChanged();
    void expenditureDeleted();

private slots:
    void addExpenditure();
    void changeExpenditure();
    void deleteExpenditure();
};

#endif // EXPENDITURE_H
