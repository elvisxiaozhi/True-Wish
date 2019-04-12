#include "inandexwidget.h"
#include "ui_inandex.h"

InAndExWidget::InAndExWidget(PaintedWidget *parent, int width) : PaintedWidget(parent, width),
    ui(new Ui::InAndEx)
{
    ui->setupUi(this);

    addAction("X");
    setOnHoverVec();
    setFixedSize(600, 250);
    setStyleSheet("QWidget { background-color: #414B66 }"
                  "#addIncome, #modifyIncome, #addEx, #modifyEx { background-color: #11B850; border: 0px; padding: 11px 20px; font: 20px; color: white; border-radius: 3px; }"
                  "#addIncome:hover, #modifyIncome:hover, #addEx:hover, #modifyEx:hover { background-color: #0A863D; }"
                  "#addIncome:pressed, #modifyIncome:pressed, #addEx:pressed, #modifyEx:pressed { background-color: #0A863D; }");

    createLineEdit();

    connect(this, &InAndExWidget::actionChanged, [this](){ hide(); });
}

InAndExWidget::~InAndExWidget()
{
    delete ui;
}

void InAndExWidget::setBinLabelAttr(CustomLabel *binLabel)
{
    ui->lineEditLayout->insertWidget(1, binLabel);
    connect(lineEdit, &CustomLineEdit::entered, [this, binLabel](){ binLabel->setPixmap(returnBinLabelPixmap(QColor(206, 216, 226), QPixmap(":/icons/recycle bin.png"))); });
    connect(lineEdit, &CustomLineEdit::left, [this, binLabel](){ binLabel->setPixmap(QPixmap()); });
}

void InAndExWidget::createLineEdit()
{
    lineEdit = new CustomLineEdit(this);
    lineEdit->setInAndExAttr();

    ui->lineEditLayout->insertWidget(1, lineEdit);
}

void InAndExWidget::mousePressEvent(QMouseEvent *event)
{
    commonPressEvent(event);

    lineEdit->clearFocus();
    emit lineEdit->isFocused(false); //emit signal here, so in CustomLineEdit class, it doesn't need focusOutEvent
}

void InAndExWidget::on_closeButton_clicked()
{
    hide();
}
