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
    setStyleSheet("QWidget { background-color: #414B66 }"
                  "#addIncome, #modifyIncome, #addEx, #modifyEx { background-color: #11B850; border: 0px; padding: 11px 20px; font: 20px; color: white; border-radius: 3px; }"
                  "#addIncome:hover, #modifyIncome:hover, #addEx:hover, #modifyEx:hover { background-color: #0A863D; }"
                  "#addIncome:pressed, #modifyIncome:pressed, #addEx:pressed, #modifyEx:pressed { background-color: #0A863D; }");

    closetAction = addAction("X");

    createLineEdit();
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

QPixmap CustomWidget::returnBinLabelPixmap(QColor color)
{
    QPixmap px(":/icons/recycle bin.png");
    QPixmap pixmap(px.size());
    pixmap.fill(color);
    pixmap.setMask(px.createMaskFromColor(Qt::transparent));

    return pixmap;
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

    lineEdit->clearFocus();
    emit lineEdit->isFocused(false); //emit signal here, so in CustomLineEdit class, it doesn't need focusOutEvent

    if (actionAt(event->pos()) == closetAction)
        hide();

    update();
}

void CustomWidget::on_closeButton_clicked()
{
    hide();
}
