#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "sidebar.h"
#include "titlebar.h"
#include "content.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private:
    Ui::MainWindow *ui;

    Sidebar *sidebar;
    TitleBar *titleBar;
//    Content *content;
};

#endif // MAINWINDOW_H
