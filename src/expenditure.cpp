#include "expenditure.h"
#include "ui_inandex.h"

Expenditure::Expenditure(CustomWidget *parent) : CustomWidget(parent)
{
    binLabel = createBinLabel();

    connect(lineEdit, &CustomLineEdit::entered, [this](){ binLabel->setPixmap(returnBinLabelPixmap(QColor(206, 216, 226))); });
    connect(lineEdit, &CustomLineEdit::left, [this](){ binLabel->setPixmap(QPixmap()); });
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

void Expenditure::setExpenditureButtons()
{
    ui->addEx->show();
    ui->modifyEx->show();
    ui->addIncome->hide();
    ui->modifyIncome->hide();
}
