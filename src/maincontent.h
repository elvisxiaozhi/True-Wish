#ifndef MAINCONTENT_H
#define MAINCONTENT_H

#include <QWidget>
#include <QDebug>
#include "income.h"
#include "expenditure.h"
#include "customlabel.h"

namespace Ui {
class MainContent;
}

class MainContent : public QWidget
{
    Q_OBJECT

public:
    explicit MainContent(QWidget *parent = 0);
    ~MainContent();

private:
    Ui::MainContent *ui;

    Income *income;
    Expenditure *expenditure;
    CustomLabel *incomeLabel, *expenditureLabel;

    void createIncomeWindow();
    void createExpenditureWindow();
    void createIncomeLabel();
    void createExpenditureLabel();
    void setIncomeWindowInfo();
    void setExpenditureWindowInfo();

protected:
    void paintEvent(QPaintEvent *);

private slots:
    void on_incomeButton_clicked();
    void changeIncome();
    void changeExpenditure();
    void on_expenditureBtn_clicked();
};

#endif // MAINCONTENT_H
