#include "maincontent.h"
#include "ui_maincontent.h"
#include <QPainter>
#include <QPaintEvent>
#include <QCompleter>

MainContent::MainContent(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::MainContent)
{
    ui->setupUi(this);

    setFixedSize(1090, 800);
    setStyleSheet("QWidget { background-color: #353F5A }");

    setComboBox();
    createIncomeWindow();
    createExpenditureWindow();
    createWishWindow();

    QString month = Database::months.value(QDate::currentDate().toString("yyyy-MM-dd").split("-")[1]);
    for (int i = 0; i < ui->comboBox->count(); ++i) {
        if (month == ui->comboBox->itemText(i)) {
            ui->comboBox->setCurrentIndex(i);
        }
    }
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

void MainContent::createWishWindow()
{
    wish = new Wish();

    createWishDetailWidget();
    setWishWindowInfo();
}

void MainContent::createYearEdit()
{
    yearEdit = new CustomLineEdit(this, 0); //set the second value to 0 for the custom placeholder text distance
    yearEdit->setFixedSize(50, 40);
    yearEdit->setStyleSheet("/*background-color: #414B66;*/ font: 20px; color: white; border: 0px;"); //Don't set background-color, uncomment to see the difference
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

    connect(yearLabel, &CustomLabel::clicked, [this](){ yearLabel->hide(); yearEdit->show();
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

void MainContent::createWishDetailWidget()
{
    wishDetail = new WishDetail(this);
    ui->wishesLayout->insertWidget(2, wishDetail);
}

void MainContent::setIncomeWindowInfo()
{
    QString date = returnSelectedDate();
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

    this->income->setChangeIncomeWindow(date);
}

void MainContent::setExpenditureWindowInfo()
{
    QString date = returnSelectedDate();
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

    this->expenditure->setChangeExpenditureWindow(date);
}

void MainContent::setWishWindowInfo()
{
    QVector<tuple<QString, int, int, int, int> > wishes = Database::returnWishInfo();
    QString wish;
    int goal = 0, years, months, days;
    tie(wish, goal, years, months, days) = wishes.first();

    if (goal == 0) {
        ui->wishInfo->setText("What are you wishing for?");
        wishDetail->hide();
        ui->wishButton->show();
    }
    else {
        ui->wishInfo->setText("Those are your wishes?");
        ui->wishButton->hide();
        wishDetail->show();
        wishDetail->setWishLableText(wish);
    }
}

void MainContent::setComboBox()
{
    createYearEdit();
    createYearLabel();

    QStringList list = Database::returnStoredMonth(yearLabel->text());
    QString currentMonth = QDate::currentDate().toString("yyyy-MM-dd").split("-")[1];
    list.push_back(currentMonth);
    sortQStringList(list);
    ui->comboBox->addItems(list);

    QLineEdit *edit = new QLineEdit(this);
    ui->comboBox->setLineEdit(edit);
    ui->comboBox->lineEdit()->setFocusPolicy(Qt::ClickFocus);
    ui->comboBox->lineEdit()->setAlignment(Qt::AlignCenter);
    ui->comboBox->setFixedSize(150, 40);
    ui->comboBox->setStyleSheet("QComboBox { background: #414B66; border: 0px; color: white; font: 20px; }"
                                "QComboBox::drop-down { border: 0px; width: 35px; }" //replace the whole arrow of the combo box
                                "QComboBox::down-arrow { image: url(:/icons/right arrow.png); width: 20px; height: 20px; }" //Define a new custom arrow icon for the combo box
                                "QComboBox::down-arrow:on { image: url(:/icons/down arrow.png); }"
                                "QComboBox QAbstractItemView { selection-background-color: #A9A9A9; }" //change the selection bgcolor
                                );

    connect(ui->comboBox, QOverload<int>::of(&QComboBox::currentIndexChanged), this, &MainContent::changeContentData);
    connect(ui->comboBox->lineEdit(), &QLineEdit::returnPressed, this, &MainContent::enterPressedOnComboEdit);

    createCompleter();
}

void MainContent::createCompleter()
{
    QStringList list;
    for (auto e : Database::months.keys()) {
        list.push_back(Database::months.value(e));
    }
    QCompleter *completer = new QCompleter(list, this);
    completer->setCaseSensitivity(Qt::CaseInsensitive);
    completer->popup()->setStyleSheet("background: #414B66; font: 20px;");
    ui->comboBox->lineEdit()->setCompleter(completer);

    connect(completer, QOverload<const QString &>::of(&QCompleter::activated), this, &MainContent::completerActivated);
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
    sortQStringList(list);
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

QString MainContent::returnSelectedDate()
{
    QString month = Database::months.key(ui->comboBox->currentText());
    QString date = QString("%1-%2-15").arg(yearLabel->text()).arg(month); //day is set to 15, but it doesn't really matter

    return date;
}

void MainContent::paintEvent(QPaintEvent *)
{
    QStyleOption opt;
    opt.init(this);
    QPainter painter(this);
    style()->drawPrimitive(QStyle::PE_Widget, &opt, &painter, this);
}

void MainContent::mousePressEvent(QMouseEvent *)
{
    ui->comboBox->lineEdit()->clearFocus();
    yearEdit->hide();
    yearLabel->show();
}

void MainContent::sortQStringList(QStringList &list)
{
    std::sort(list.begin(), list.end());
    list.erase(std::unique(list.begin(), list.end()), list.end());

    for (int i = 0; i < list.size(); ++i) {
        list[i] = Database::months.value(list[i]);
    }
}

void MainContent::on_incomeButton_clicked()
{
    setWindowToTop(income);
    income->setAddIncomeWindow(returnSelectedDate());
}

void MainContent::changeIncome()
{
    setIncomeWindowInfo();
    setWindowToTop(income);
}

void MainContent::changeExpenditure()
{
    setExpenditureWindowInfo();
    setWindowToTop(expenditure);
}

void MainContent::changeWish()
{
    qDebug() << "Change wish";
}

void MainContent::on_expenditureBtn_clicked()
{
    setWindowToTop(expenditure);
    expenditure->setAddExpenditureWindow(returnSelectedDate());
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

void MainContent::enterPressedOnComboEdit()
{
    ui->comboBox->lineEdit()->clearFocus();
}

void MainContent::changeContentData(int)
{
    setIncomeWindowInfo();
    setExpenditureWindowInfo();
}

void MainContent::completerActivated(const QString &text)
{
    ui->comboBox->clear();
    QStringList list = Database::returnStoredMonth(yearLabel->text());
    list.push_back(QString(Database::months.key(text)));
    sortQStringList(list);
    ui->comboBox->addItems(list);

    for (int i = 0; i < list.size(); ++i) {
        if (text == list[i]) {
            ui->comboBox->setCurrentIndex(i);
        }
    }
}

void MainContent::on_wishButton_clicked()
{
    wish->show();
}
