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
    void setIncomeWindowInfo(QString date = QDate::currentDate().toString("yyyy-MM-dd"));
    void setExpenditureWindowInfo(QString date = QDate::currentDate().toString("yyyy-MM-dd"));
    void setComboBox();
    void createCompleter();
    void setWindowToTop(QWidget *);
    void resetComboBox();
    QString returnSelectedDate();
    void paintEvent(QPaintEvent *);
    void mousePressEvent(QMouseEvent *);
    void sortQStringList(QStringList &, const bool isValue = 0); //set isValue to 1 if Database::returnStoredMonth() is not called

private slots:
    void on_incomeButton_clicked();
    void changeIncome();
    void changeExpenditure();
    void on_expenditureBtn_clicked();
    void enterPressedOnYearEdit();
    void enterPressedOnComboEdit();
    void changeContentData(int);
    void completerActivated(const QString &);
};

#endif // MAINCONTENT_H
