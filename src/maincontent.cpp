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

void MainContent::createYearEdit()
{
    yearEdit = new CustomLineEdit(this, 0); //set the second value to 0 for the custom placeholder text distance
    yearEdit->setFixedSize(50, 40);
    yearEdit->setStyleSheet("background-color: #414B66; font: 20px; color: white;");
    yearEdit->hide();

    ui->comboLayout->addWidget(yearEdit);

    connect(yearEdit, &CustomLineEdit::returnPressed, this, &MainContent::enterPressedOnYearEdit);
}

void MainContent::createYearLabel()
{
    yearLabel = new CustomLabel(this);
    yearLabel->setText(QString::number(QDate::currentDate().year()));
    yearLabel->setAlignment(Qt::AlignCenter);
    yearLabel->setFixedSize(50, 40);
    yearLabel->setStyleSheet("color: white; font: 20px;");

    ui->comboLayout->addWidget(yearLabel);

    connect(yearLabel, &CustomLabel::doubleClicked, [this](){ yearLabel->hide(); yearEdit->show();
        yearEdit->setCustomPlaceholderText(yearLabel->text()); });
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

void MainContent::setIncomeWindowInfo(QString date)
{
    int income = get<1>(Income::updateIncomeInfo(date));

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

void MainContent::setExpenditureWindowInfo(QString date)
{
    int expenditure = get<1>(Expenditure::updateExpenditureInfo(date));

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
    createYearEdit();
    createYearLabel();

    ui->comboBox->addItems(Database::returnStoredMonth(yearLabel->text()));

    QLineEdit *edit = new QLineEdit(this);
    ui->comboBox->setLineEdit(edit);
    ui->comboBox->lineEdit()->setReadOnly(true);
    ui->comboBox->lineEdit()->setAlignment(Qt::AlignCenter);

    ui->comboBox->setFixedSize(150, 40);
    ui->comboBox->setStyleSheet("QComboBox { background: #414B66; border: 0px; color: white; font: 20px; }"
                                "QComboBox::drop-down { border: 0px; width: 35px; }" //replace the whole arrow of the combo box
                                "QComboBox::down-arrow { image: url(:/icons/right arrow.png); width: 20px; height: 20px; }" //Define a new custom arrow icon for the combo box
                                "QComboBox::down-arrow:on { image: url(:/icons/down arrow.png); }"
                                "QComboBox QAbstractItemView { selection-background-color: #A9A9A9; }" //change the selection bgcolor
                                );

    connect(ui->comboBox, QOverload<int>::of(&QComboBox::currentIndexChanged), this, &MainContent::changeContentData);
}

//make sure winodw stays in the front
void MainContent::setWindowToTop(QWidget *w)
{
    w->show();
    w->raise();
    w->activateWindow();
}

void MainContent::resetComboBox()
{
    QString item = ui->comboBox->currentText();
    ui->comboBox->clear();

    QStringList list = Database::returnStoredMonth(yearLabel->text());
    if (list.empty()) {
        ui->comboBox->insertItem(0, item);
    }
    else {
        ui->comboBox->addItems(list);
        for (int i = 0; i < list.size(); ++i) {
            if (item == list[i]) {
                ui->comboBox->setCurrentIndex(i);
                break;
            }
        }
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
    setWindowToTop(income);
    income->setAddIncomeWindow();
}

void MainContent::changeIncome()
{
    setIncomeWindowInfo();
    income->setChangeIncomeWindow();
    setWindowToTop(income);
}

void MainContent::changeExpenditure()
{
    setExpenditureWindowInfo();
    expenditure->setChangeExpenditureWindow();
    setWindowToTop(expenditure);
}

void MainContent::on_expenditureBtn_clicked()
{
    setWindowToTop(expenditure);
    expenditure->setAddExpenditureWindow();
}

void MainContent::enterPressedOnYearEdit()
{
    yearEdit->hide();
    yearLabel->show();
    if (yearEdit->text() != "") {
        yearLabel->setText(yearEdit->text());
    }
    yearEdit->setText("");

    resetComboBox();
}

void MainContent::changeContentData(int index)
{
    QString month = Database::months.key(ui->comboBox->itemText(index));
    QString date = QString("%1-%2-15").arg(yearLabel->text()).arg(month); //day is set to 15, but it doesn't really matter
    setIncomeWindowInfo(date);
    setExpenditureWindowInfo(date);
}
