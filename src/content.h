#ifndef CONTENT_H
#define CONTENT_H

#include <QWidget>

namespace Ui {
class Content;
}

class Content : public QWidget
{
    Q_OBJECT

public:
    explicit Content(QWidget *parent = 0);
    ~Content();

private:
    Ui::Content *ui;
};

#endif // CONTENT_H
