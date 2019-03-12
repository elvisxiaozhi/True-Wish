#include "income.h"
#include "ui_inandex.h"

int Income::income;
QString Income::incomeAddedDate;

Income::Income(CustomWidget *parent) :
    CustomWidget(parent)
{
    ui->addIncome->show();
    ui->modifyIncome->show();
    ui->addEx->hide();
    ui->modifyEx->hide();

    createBinLabel();

    connect(ui->addIncome, &QPushButton::clicked, this, &Income::addIncome);
    connect(ui->modifyIncome, &QPushButton::clicked, this, &Income::changeIncome);
    connect(lineEdit, &CustomLineEdit::entered, [this](){ binLabel->setPixmap(returnBinLabelPixmap(QColor(206, 216, 226))); });
    connect(lineEdit, &CustomLineEdit::left, [this](){ binLabel->setPixmap(QPixmap()); });
}

Income::~Income()
{
}

void Income::setAddIncomeWindow()
{
    ui->title->setText("Add Income");
    lineEdit->setCustomPlaceholderText("How much money did you make this month?");
    ui->addIncome->show();
    ui->modifyIncome->hide();
    binLabel->hide();
}

void Income::setChangeIncomeWindow()
{
    ui->title->setText("Change Income");
    ui->addIncome->hide();
    ui->modifyIncome->show();
    binLabel->show();

    QString str = QString("You made %1 this month.").arg(income);
    lineEdit->setCustomPlaceholderText(str);
}

tuple<QString, int> Income::updateIncomeInfo()
{
    tie(incomeAddedDate, income) = Database::returnIncomeInfo(QDate::currentDate().toString("yyyy-MM"));

    return make_tuple(incomeAddedDate, income);
}

void Income::createBinLabel()
{
    binLabel = new CustomLabel(this);
    binLabel->setFixedSize(30, 30);

    ui->lineEditLayout->insertWidget(1, binLabel);

    connect(binLabel, &CustomLabel::clicked, this, &Income::deleteIncome);
    connect(binLabel, &CustomLabel::entered, [this](){ binLabel->setPixmap(returnBinLabelPixmap(QColor(255, 255, 255))); });
    connect(binLabel, &CustomLabel::left, [this](){ binLabel->setPixmap(QPixmap()); });
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
