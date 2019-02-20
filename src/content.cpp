#include "content.h"
#include "ui_content.h"

Content::Content(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Content)
{
    ui->setupUi(this);
}

Content::~Content()
{
    delete ui;
}
