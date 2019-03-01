#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QStandardPaths>
#include <QDir>
#include <QXmlStreamWriter>
#include <QXmlStreamReader>
#include <QDebug>

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

    createDataFile();
    writeData();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::createDataFile()
{
    QString path = QStandardPaths::standardLocations(QStandardPaths::HomeLocation).first() + "/AppData/Local/True Wish";

    if(!QDir().exists(path))
        QDir().mkdir(path);

    userDataPath = path + "/User Data.xml";
    QFile file(userDataPath);

    if (!file.open(QIODevice::ReadWrite))
        qDebug() << file.error();

    file.close();
}

void MainWindow::writeData(QString income, QString expenditure)
{
    QFile file(userDataPath);
    QXmlStreamWriter writer(&file);
    writer.setAutoFormatting(true);

    if (!file.open(QIODevice::WriteOnly))
        qDebug() << file.error();

    writer.writeStartDocument();

    writer.writeStartElement("data");

    writer.writeTextElement("income", income);
    writer.writeTextElement("expenditure", expenditure);

    writer.writeEndDocument();

    writer.writeEndDocument();

    file.close();
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
