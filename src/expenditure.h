#ifndef EXPENDITURE_H
#define EXPENDITURE_H

#include <QWidget>

namespace Ui {
class InAndEx;
}

class Expenditure : public QWidget
{
    Q_OBJECT
public:
    explicit Expenditure(QWidget *parent = nullptr);
    ~Expenditure();

private:
    Ui::InAndEx *ui;
};

#endif // EXPENDITURE_H
