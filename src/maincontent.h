#ifndef MAINCONTENT_H
#define MAINCONTENT_H

#include <QWidget>
#include <QDebug>
#include "income.h"
#include "expenditure.h"
#include "customlabel.h"
#include "wish.h"
#include "wishdetail.h"

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
    Wish *wish;
    WishDetail *wishDetail;
    CustomLabel *yearLabel, *incomeLabel, *expenditureLabel;
    CustomLineEdit *yearEdit;
    QVector<tuple<QString, QString, int, int, int, int> > wishes;

    void createIncomeWindow();
    void createExpenditureWindow();
    void createWishWindow();
    void createYearEdit();
    void createYearLabel();
    void createIncomeLabel();
    void createExpenditureLabel();
    void createWishDetailWidget();
    void setIncomeWindowInfo();
    void setExpenditureWindowInfo();
    void setWishDetail(QString, QString, int, int, int, int);
    void setWishWindowInfo();
    void setComboBox();
    void createCompleter();
    void setWindowToTop(QWidget *);
    void resetComboBox();
    QString returnSelectedDate();
    void paintEvent(QPaintEvent *);
    void mousePressEvent(QMouseEvent *);
    void sortQStringList(QStringList &);

private slots:
    void on_incomeButton_clicked();
    void changeIncome();
    void changeExpenditure();
    void changeWish();
    void on_expenditureBtn_clicked();
    void enterPressedOnYearEdit();
    void enterPressedOnComboEdit();
    void changeContentData(int);
    void completerActivated(const QString &);
    void on_wishButton_clicked();
    void changeWishDetail(bool isNextWish = true);
};

#endif // MAINCONTENT_H
