#include "customwidget.h"
#include "ui_inandex.h"
#include <QPainter>
#include <QPaintEvent>
#include <QWindow>
#include <windows.h>
#include <QBitmap>

CustomWidget::CustomWidget(QWidget *parent) : QWidget(parent),
    ui(new Ui::InAndEx)
{
    ui->setupUi(this);

    setMouseTracking(this);
    setWindowFlags(Qt::FramelessWindowHint);
    setFixedSize(600, 250);
    setStyleSheet("QWidget { background-color: #414B66 }");

    closetAction = addAction("X");

    createLineEdit();
    createBinLabel();
    createLine();
}

CustomWidget::~CustomWidget()
{
    delete ui;
}

QAction *CustomWidget::addAction(const QString &text)
{
    QAction *action = new QAction(text, this);
    action->setCheckable(true);

    return action;
}

QAction *CustomWidget::actionAt(const QPoint &point)
{
    int posX = 570;
    QRect rec(posX, 10, 35, 35);

    if (rec.contains(point))
        return closetAction;

    return nullptr;
}

void CustomWidget::createLineEdit()
{
    lineEdit = new CustomLineEdit(this);
    lineEdit->setFrame(false);
    lineEdit->setFixedSize(525, 30);

    ui->lineEditLayout->insertWidget(0, lineEdit);

    connect(lineEdit, &CustomLineEdit::entered, [this](){ setBinLabelPixmap(QColor(206, 216, 226)); });
    connect(lineEdit, &CustomLineEdit::left, [this](){ binLabel->setPixmap(QPixmap()); });
}

void CustomWidget::createBinLabel()
{
    binLabel = new CustomLabel(this);
    binLabel->setFixedSize(30, 30);

    ui->lineEditLayout->insertWidget(1, binLabel);

//    connect(binLabel, &CustomLabel::clicked, this, &Income::deleteIncome);
    connect(binLabel, &CustomLabel::entered, [this](){ setBinLabelPixmap(QColor(255, 255, 255)); });
    connect(binLabel, &CustomLabel::left, [this](){ binLabel->setPixmap(QPixmap()); });
}

void CustomWidget::createLine()
{
    ui->lineWidget->setFixedSize(540, 1);

    connect(lineEdit, &CustomLineEdit::isFocused, [this](bool isFocused){
        if (isFocused)
            ui->lineWidget->setStyleSheet("background-color: white;");
        else
            ui->lineWidget->setStyleSheet("background-color: #BFC6D6;");
    });
}

void CustomWidget::setBinLabelPixmap(QColor color)
{
    QPixmap px(":/icons/recycle bin.png");
    QPixmap pixmap(px.size());
    pixmap.fill(color);
    pixmap.setMask(px.createMaskFromColor(Qt::transparent));

    binLabel->setPixmap(pixmap);
}

void CustomWidget::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);
    painter.setFont(QFont("Times", 13));

    QPen pen;
    if (onHover) {
        pen.setBrush(Qt::white);
    }
    else {
        pen.setBrush(QColor(152, 160, 179));
    }

    QRect textRect(570, 10, event->rect().width(), event->rect().height());
    painter.setPen(pen);
    painter.drawText(textRect, closetAction->text());
}

void CustomWidget::mouseMoveEvent(QMouseEvent *event)
{
    if (actionAt(event->pos()) == closetAction) {
        onHover = true;
    }
    else {
        onHover = false;
    }

    update();
}

void CustomWidget::mousePressEvent(QMouseEvent *event)
{
    //use native windows api to move window
    if (event->buttons().testFlag(Qt::LeftButton))
    {
        HWND hWnd = ::GetAncestor((HWND)(window()->windowHandle()->winId()), GA_ROOT);
        POINT pt;
        ::GetCursorPos(&pt);
        ::ReleaseCapture();
        ::SendMessage(hWnd, WM_NCLBUTTONDOWN, HTCAPTION, POINTTOPOINTS(pt));
    }

//    lineEdit->clearFocus();
//    emit lineEdit->isFocused(false); //emit signal here, so in CustomLineEdit class, it doesn't need focusOutEvent

    if (actionAt(event->pos()) == closetAction)
        hide();

    update();
}
