#include "income.h"
#include "ui_inandex.h"
#include <QPaintEvent>
#include <QPainter>
#include <QDebug>
#include <windows.h>
#include <QWindow>
#include <QBitmap>

int Income::income;
QString Income::incomeAddedDate;

Income::Income(CustomWidget *parent) :
    CustomWidget(parent)
{
    connect(ui->addButton, &QPushButton::clicked, this, &Income::addIncome);
    connect(ui->modifyButton, &QPushButton::clicked, this, &Income::changeIncome);
    connect(binLabel, &CustomLabel::clicked, this, &Income::deleteIncome);
}

Income::~Income()
{
}

void Income::setAddIncomeWindow()
{
    ui->title->setText("Add Income");
    lineEdit->setCustomPlaceholderText("How much money did you make this month?");
    ui->addButton->show();
    ui->modifyButton->hide();
    binLabel->hide();
}

void Income::setChangeIncomeWindow()
{
    ui->title->setText("Change Income");
    ui->addButton->hide();
    ui->modifyButton->show();
    binLabel->show();

    QString str = QString("You made %1 this month.").arg(income);
    lineEdit->setCustomPlaceholderText(str);
}

void Income::updateIncomeInfo()
{
    tie(incomeAddedDate, income) = Database::returnIncomeInfo(QDate::currentDate().toString("yyyy-MM"));
}

void Income::addIncome()
{
    setAddIncomeWindow();

    Database::addIncome(QDate::currentDate().toString("yyyy-MM-dd"), lineEdit->text().toInt());
    lineEdit->setText(QString(""));  //clear line edit text after modify button is clicked, clear function is not working here
    hide();

    emit incomeAdded();
}

void Income::changeIncome()
{
    Database::changeIncome(incomeAddedDate, lineEdit->text().toInt());
    lineEdit->setText(QString(""));
    hide();

    emit incomeChanged();
}

void Income::deleteIncome()
{
    Database::deleteIncome(incomeAddedDate);
    hide();

    emit incomeDeleted();
}
