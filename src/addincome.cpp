#include "addincome.h"
#include "ui_addincome.h"
#include <QPaintEvent>
#include <QPainter>
#include <QDebug>
#include <windows.h>
#include <QWindow>

AddIncome::AddIncome(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::AddIncome)
{
    ui->setupUi(this);

    setMouseTracking(this);
    setWindowFlags(Qt::FramelessWindowHint);
    setFixedSize(600, 250);

    closetAction = addAction("X");

    createLineEdit();
    createLine();

    setStyleSheet("QWidget { background-color: #414B66 }");
}

AddIncome::~AddIncome()
{
    delete ui;
}

QAction *AddIncome::addAction(const QString &text)
{
    QAction *action = new QAction(text, this);
    action->setCheckable(true);

    return action;
}

QAction *AddIncome::actionAt(const QPoint &point)
{
    int posX = 570;
    QRect rec(posX, 10, 35, 35);

    if (rec.contains(point))
        return closetAction;

    return nullptr;
}

void AddIncome::createLineEdit()
{
    lineEdit = new CustomLineEdit(this);

    ui->lineEditLayout->addWidget(lineEdit);
}

void AddIncome::createLine()
{
    ui->lineWidget->setFixedSize(540, 1);

    connect(lineEdit, &CustomLineEdit::isFocused, [this](bool isFocused){
        if (isFocused)
            ui->lineWidget->setStyleSheet("background-color: white;");
        else
            ui->lineWidget->setStyleSheet("background-color: #BFC6D6;");
    });
}

void AddIncome::paintEvent(QPaintEvent *event)
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

void AddIncome::mouseMoveEvent(QMouseEvent *event)
{
    if (actionAt(event->pos()) == closetAction) {
        onHover = true;
    }
    else {
        onHover = false;
    }

    update();
}

void AddIncome::mousePressEvent(QMouseEvent *event)
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

void AddIncome::on_closeButton_clicked()
{
    hide();
}
