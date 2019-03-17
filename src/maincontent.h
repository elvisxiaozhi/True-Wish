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
    CustomLabel *yearLabel, *incomeLabel, *expenditureLabel;
    CustomLineEdit *yearEdit;

    void createIncomeWindow();
    void createExpenditureWindow();
    void createYearEdit();
    void createYearLabel();
    void createIncomeLabel();
    void createExpenditureLabel();
    void setIncomeWindowInfo();
    void setExpenditureWindowInfo();
    void setComboBox();
    void setWindowToTop(QWidget *);

protected:
    void paintEvent(QPaintEvent *);

private slots:
    void on_incomeButton_clicked();
    void changeIncome();
    void changeExpenditure();
    void on_expenditureBtn_clicked();
    void enterPressedOnYearEdit();
};

#endif // MAINCONTENT_H
