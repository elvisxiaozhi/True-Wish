#include "expenditure.h"
#include "ui_inandex.h"

int Expenditure::expenditure;
QString Expenditure::expenditureAddedDate;

Expenditure::Expenditure(CustomWidget *parent) : CustomWidget(parent)
{
    binLabel = createBinLabel();
    connect(binLabel, &CustomLabel::clicked, this, &Expenditure::deleteExpenditure);

    connect(ui->addEx, &QPushButton::clicked, this, &Expenditure::addExpenditure);
    connect(ui->modifyEx, &QPushButton::clicked, this, &Expenditure::changeExpenditure);
}

Expenditure::~Expenditure()
{

}

void Expenditure::setAddExpenditureWindow()
{
    setExpenditureButtons();
    ui->modifyEx->hide();

    ui->title->setText("Add Expenditure");
    lineEdit->setCustomPlaceholderText("How much money did you spend this month?");
    binLabel->hide();
}

void Expenditure::setChangeExpenditureWindow()
{
    setExpenditureButtons();
    ui->addEx->hide();

    ui->title->setText("Change Expenditure");
    binLabel->show();

    QString str = QString("You made %1 this month.").arg(expenditure);
    lineEdit->setCustomPlaceholderText(str);
}

tuple<QString, int> Expenditure::updateExpenditureInfo()
{
    tie(expenditureAddedDate, expenditure) = Database::returnExpenditureInfo(QDate::currentDate().toString("yyyy-MM"));

    return make_tuple(expenditureAddedDate, expenditure);
}

void Expenditure::setExpenditureButtons()
{
    ui->addEx->show();
    ui->modifyEx->show();
    ui->addIncome->hide();
    ui->modifyIncome->hide();
}

void Expenditure::addExpenditure()
{
    setAddExpenditureWindow();

    Database::addExpenditure(QDate::currentDate().toString("yyyy-MM-dd"), lineEdit->text().toInt());
    lineEdit->setText(QString(""));  //clear line edit text after modify button is clicked, clear function is not working here
    hide();

    emit expenditureAdded();
}

void Expenditure::changeExpenditure()
{
    Database::changeExpenditure(expenditureAddedDate, lineEdit->text().toInt());
    lineEdit->setText(QString(""));
    hide();

    emit expenditureChanged();
}

void Expenditure::deleteExpenditure()
{
    Database::deleteExpendture(expenditureAddedDate);
    hide();

    emit expenditureDeleted();
}
