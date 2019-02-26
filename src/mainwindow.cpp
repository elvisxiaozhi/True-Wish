#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    titleBar = new TitleBar(this);
    sidebar = new Sidebar(this);
    content = new MainContent(this);

    ui->gridLayout->addWidget(titleBar, 0, 0, 1, 0, Qt::AlignCenter);
    ui->gridLayout->addWidget(sidebar, 1, 0);
    ui->gridLayout->addWidget(content, 1, 1);

    connect(titleBar, &TitleBar::actionChanged, this, &MainWindow::titleBarClicked);

    setWindowFlags(Qt::FramelessWindowHint);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::titleBarClicked(int index)
{
    if (index == 0) {
        showMinimized();
    }
    else if (index == 1) {
        close();
    }
}
