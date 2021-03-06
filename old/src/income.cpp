#include "income.h"
#include "ui_inandex.h"

int Income::income;
QString Income::incomeAddedDate;

Income::Income(InAndExWidget *parent) :
    InAndExWidget(parent)
{
    binLabel = createBinLabel();
    setBinLabelAttr(binLabel);
    connect(binLabel, &CustomLabel::clicked, this, &Income::deleteIncome);

    connect(ui->addIncome, &QPushButton::clicked, this, &Income::addIncome);
    connect(ui->modifyIncome, &QPushButton::clicked, this, &Income::changeIncome);
}

Income::~Income()
{
}

void Income::setIncomeButtons()
{
    ui->addIncome->show();
    ui->modifyIncome->show();
    ui->addEx->hide();
    ui->modifyEx->hide();
}

void Income::setAddIncomeWindow(const QString date)
{
    incomeAddedDate = date;

    setIncomeButtons();
    ui->modifyIncome->hide();

    ui->title->setText("Add Income");
    lineEdit->setCustomPlaceholderText("How much money did you make this month?");
    binLabel->hide();
}

void Income::setChangeIncomeWindow(const QString date)
{
    incomeAddedDate = date;

    setIncomeButtons();
    ui->addIncome->hide();

    ui->title->setText("Change Income");
    binLabel->show();

    QString str = QString("You made %1 this month.").arg(income);
    lineEdit->setCustomPlaceholderText(str);
}

tuple<QString, int> Income::updateIncomeInfo(QString date)
{
    tie(incomeAddedDate, income) = Database::returnIncomeInfo(date);

    return make_tuple(incomeAddedDate, income);
}

void Income::addIncome()
{
    Database::addIncome(incomeAddedDate, lineEdit->text().toInt());
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
