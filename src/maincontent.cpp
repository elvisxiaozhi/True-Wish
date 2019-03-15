#include "maincontent.h"
#include "ui_maincontent.h"
#include <QPainter>
#include <QPaintEvent>

MainContent::MainContent(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::MainContent)
{
    ui->setupUi(this);

    setFixedSize(1090, 800);
    setStyleSheet("QWidget { background-color: #353F5A }");

    createIncomeWindow();
    createExpenditureWindow();
    setComboBox();
}

MainContent::~MainContent()
{
    delete ui;
}

void MainContent::createIncomeWindow()
{
    income = new Income();

    connect(income, &Income::incomeAdded, [this](){ setIncomeWindowInfo(); });
    connect(income, &Income::incomeChanged, [this](){ setIncomeWindowInfo(); });
    connect(income, &Income::incomeDeleted, [this](){ setIncomeWindowInfo(); });

    createIncomeLabel();
    setIncomeWindowInfo();
}

void MainContent::createExpenditureWindow()
{
    expenditure = new Expenditure();

    connect(expenditure, &Expenditure::expenditureAdded, [this](){ setExpenditureWindowInfo(); });
    connect(expenditure, &Expenditure::expenditureChanged, [this](){ setExpenditureWindowInfo(); });
    connect(expenditure, &Expenditure::expenditureDeleted, [this](){ setExpenditureWindowInfo(); });

    createExpenditureLabel();
    setExpenditureWindowInfo();
}

void MainContent::createIncomeLabel()
{
    incomeLabel = new CustomLabel(this);
    incomeLabel->setInAndExAttr();

    connect(incomeLabel, &CustomLabel::doubleClicked, this, &MainContent::changeIncome);

    ui->incomeLayout->insertWidget(2, incomeLabel);
}

void MainContent::createExpenditureLabel()
{
    expenditureLabel = new CustomLabel(this);
    expenditureLabel->setInAndExAttr();

    connect(expenditureLabel, &CustomLabel::doubleClicked, this, &MainContent::changeExpenditure);

    ui->expenditureLayout->insertWidget(2, expenditureLabel);
}

void MainContent::setIncomeWindowInfo()
{
    int income = get<1>(Income::updateIncomeInfo());

    if (income == 0) {
        ui->incomeInfo->setText("How much money did you make this month?");
        incomeLabel->hide();
        ui->incomeButton->show();
    }
    else {
        ui->incomeInfo->setText("This month you made");
        ui->incomeButton->hide();
        incomeLabel->show();
        incomeLabel->setText(QString::number(income));
    }
}

void MainContent::setExpenditureWindowInfo()
{
    int expenditure = get<1>(Expenditure::updateExpenditureInfo());

    if (expenditure == 0) {
        ui->expenditureInfo->setText("How much money did you spend this month?");
        expenditureLabel->hide();
        ui->expenditureBtn->show();
    }
    else {
        ui->expenditureInfo->setText("This month you made");
        ui->expenditureBtn->hide();
        expenditureLabel->show();
        expenditureLabel->setText(QString::number(expenditure));
    }
}

void MainContent::setComboBox()
{
    QStringList list;
    list.push_back("March 2019");
    list.push_back("April 2019");
    ui->comboBox->addItems(list);
}

void MainContent::paintEvent(QPaintEvent *)
{
    QStyleOption opt;
    opt.init(this);
    QPainter painter(this);
    style()->drawPrimitive(QStyle::PE_Widget, &opt, &painter, this);
}

void MainContent::on_incomeButton_clicked()
{
    income->show();
    //make sure this winodw stays in the front
    income->raise();
    income->activateWindow();
    income->setAddIncomeWindow();
}

void MainContent::changeIncome()
{
    setIncomeWindowInfo();
    income->setChangeIncomeWindow();
    income->show();
}

void MainContent::changeExpenditure()
{
    setExpenditureWindowInfo();
    expenditure->setChangeExpenditureWindow();
    expenditure->show();
}

void MainContent::on_expenditureBtn_clicked()
{
    expenditure->show();
    expenditure->raise();
    expenditure->activateWindow();
    expenditure->setAddExpenditureWindow();
}
