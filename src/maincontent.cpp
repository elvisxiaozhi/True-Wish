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

    income = new AddIncome();
}

MainContent::~MainContent()
{
    delete ui;
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
}
