#ifndef MAINCONTENT_H
#define MAINCONTENT_H

#include <QWidget>

namespace Ui {
class MainContent;
}

class MainContent : public QWidget
{
    Q_OBJECT

public:
    explicit MainContent(QWidget *parent = 0);
    ~MainContent();

private:
    Ui::MainContent *ui;

protected:
    void paintEvent(QPaintEvent *);
};

#endif // MAINCONTENT_H
