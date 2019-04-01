#include "customwidget.h"
#include "ui_inandex.h"
#include <QBitmap>

CustomWidget::CustomWidget(PaintedWidget *parent, int width) : PaintedWidget(parent, width),
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
    createLine();

    connect(this, &CustomWidget::actionChanged, [this](){ hide(); });
}

CustomWidget::~CustomWidget()
{
    delete ui;
}

void CustomWidget::createLineEdit()
{
    lineEdit = new CustomLineEdit(this);
    lineEdit->setInAndExAttr();

    ui->lineEditLayout->insertWidget(0, lineEdit);
}

void CustomWidget::createLine()
{
    ui->lineWidget->setFixedSize(540, 1);
    lineEdit->changeFocuseEffect(ui->lineWidget);
}

void CustomWidget::mousePressEvent(QMouseEvent *event)
{
    commonPressEvent(event);

    lineEdit->clearFocus();
    emit lineEdit->isFocused(false); //emit signal here, so in CustomLineEdit class, it doesn't need focusOutEvent
}

QPixmap CustomWidget::returnBinLabelPixmap(QColor color)
{
    QPixmap px(":/icons/recycle bin.png");
    QPixmap pixmap(px.size());
    pixmap.fill(color);
    pixmap.setMask(px.createMaskFromColor(Qt::transparent));

    return pixmap;
}

CustomLabel *CustomWidget::createBinLabel()
{
    CustomLabel *binLabel = new CustomLabel(this);
    binLabel->setFixedSize(30, 30);

    ui->lineEditLayout->insertWidget(1, binLabel);

    connect(lineEdit, &CustomLineEdit::entered, [this, binLabel](){ binLabel->setPixmap(returnBinLabelPixmap(QColor(206, 216, 226))); });
    connect(lineEdit, &CustomLineEdit::left, [this, binLabel](){ binLabel->setPixmap(QPixmap()); });
    connect(binLabel, &CustomLabel::entered, [this, binLabel](){ binLabel->setPixmap(returnBinLabelPixmap(QColor(255, 255, 255))); });
    connect(binLabel, &CustomLabel::left, [this, binLabel](){ binLabel->setPixmap(QPixmap()); });

    return binLabel;
}

void CustomWidget::on_closeButton_clicked()
{
    hide();
}
