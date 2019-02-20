#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    titleBar = new TitleBar(this);
    sidebar = new Sidebar(this);
//    content = new Content(this);

    ui->gridLayout->addWidget(titleBar, 0, 0);
    ui->gridLayout->addWidget(sidebar, 1, 0);
//    ui->gridLayout->addWidget(content, 1, 1);
}

MainWindow::~MainWindow()
{
    delete ui;
}
