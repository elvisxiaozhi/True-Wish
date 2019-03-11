#include "expenditure.h"
#include "ui_inandex.h"

Expenditure::Expenditure(QWidget *parent) : QWidget(parent),
    ui(new Ui::InAndEx)
{
    ui->setupUi(this);
}

Expenditure::~Expenditure()
{

}
