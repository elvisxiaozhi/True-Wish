#include "expenditure.h"
#include "ui_inandex.h"

int Expenditure::expenditure;
QString Expenditure::expenditureAddedDate;

Expenditure::Expenditure(InAndExWidget *parent) : InAndExWidget(parent)
{
    binLabel = createBinLabel();
    setBinLabelAttr(binLabel);
    connect(binLabel, &CustomLabel::clicked, this, &Expenditure::deleteExpenditure);

    connect(ui->addEx, &QPushButton::clicked, this, &Expenditure::addExpenditure);
    connect(ui->modifyEx, &QPushButton::clicked, this, &Expenditure::changeExpenditure);
}

Expenditure::~Expenditure()
{

}

void Expenditure::setAddExpenditureWindow(const QString date)
{
    expenditureAddedDate = date;

    setExpenditureButtons();
    ui->modifyEx->hide();

    ui->title->setText("Add Expenditure");
    lineEdit->setCustomPlaceholderText("How much money did you spend this month?");
    binLabel->hide();
}

void Expenditure::setChangeExpenditureWindow(const QString date)
{
    expenditureAddedDate = date;

    setExpenditureButtons();
    ui->addEx->hide();

    ui->title->setText("Change Expenditure");
    binLabel->show();

    QString str = QString("You made %1 this month.").arg(expenditure);
    lineEdit->setCustomPlaceholderText(str);
}

tuple<QString, int> Expenditure::updateExpenditureInfo(QString date)
{
    tie(expenditureAddedDate, expenditure) = Database::returnExpenditureInfo(date);

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
    Database::addExpenditure(expenditureAddedDate, lineEdit->text().toInt());
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
