#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    sidebar = new Sidebar(this);
    addDockWidget(Qt::LeftDockWidgetArea, sidebar);

    titleBar = new TitleBar(this);

//    ui->widget->setLayout(ui->);
    ui->contentLayout->addWidget(titleBar);
}

MainWindow::~MainWindow()
{
    delete ui;
}
