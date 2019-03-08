#ifndef MAINCONTENT_H
#define MAINCONTENT_H

#include <QWidget>
#include <QDebug>
#include "addincome.h"
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

    AddIncome *income;
    CustomLabel *incomeLabel;

    void setIncome();

protected:
    void paintEvent(QPaintEvent *);

private slots:
    void on_incomeButton_clicked();
    void changeIncome();
};

#endif // MAINCONTENT_H
