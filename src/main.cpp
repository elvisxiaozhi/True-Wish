#include "mainwindow.h"
#include <QApplication>
#include "wish.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();

    Wish p;
    p.show();

    return a.exec();
}
