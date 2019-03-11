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

    income = new Income();
    connect(income, &Income::incomeAdded, [this](){ setIncomeWindowInfo(); });
    connect(income, &Income::incomeChanged, [this](){ setIncomeWindowInfo(); });
    connect(income, &Income::incomeDeleted, [this](){ setIncomeWindowInfo(); });

    expenditure = new Expenditure();

    createIncomeLabel();
    setIncomeWindowInfo();
}

MainContent::~MainContent()
{
    delete ui;
}

void MainContent::createIncomeLabel()
{
    incomeLabel = new CustomLabel(this);

    incomeLabel->setStyleSheet("background-color: #11B850; border: 0px; padding: 15px 20px; font: 60px; color: white; border-radius: 3px;");
    incomeLabel->setAlignment(Qt::AlignCenter);
    incomeLabel->setFixedSize(250, 100);

    incomeLabel->hide();

    connect(incomeLabel, &CustomLabel::doubleClicked, this, &MainContent::changeIncome);

    ui->incomeLayout->insertWidget(2, incomeLabel);
}

void MainContent::setIncomeWindowInfo()
{
    Income::updateIncomeInfo();

    if (Income::income == 0) {
        ui->incomeInfo->setText("How much money did you make this month?");
        incomeLabel->hide();
        ui->incomeButton->show();
    }
    else {
        ui->incomeInfo->setText("This month you made");
        ui->incomeButton->hide();
        incomeLabel->show();
        incomeLabel->setText(QString::number(Income::income));
    }
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
    income->addIncome();
}

void MainContent::changeIncome()
{
    setIncomeWindowInfo();
    income->changeIncome();
    income->show();
}

void MainContent::on_expenditureBtn_clicked()
{
    expenditure->show();
    expenditure->raise();
    expenditure->activateWindow();
}
