#include "addincome.h"
#include "ui_addincome.h"
#include <QPaintEvent>
#include <QPainter>
#include <QDebug>
#include <windows.h>
#include <QWindow>
#include <QBitmap>

AddIncome::AddIncome(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::AddIncome)
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

    connect(lineEdit, &CustomLineEdit::entered, [this](){ setBinLabelPixmap(QColor(206, 216, 226)); });
    connect(lineEdit, &CustomLineEdit::left, [this](){ binLabel->setPixmap(QPixmap()); });
    connect(binLabel, &CustomLabel::entered, [this](){ setBinLabelPixmap(QColor(255, 255, 255)); });
    connect(binLabel, &CustomLabel::left, [this](){ setBinLabelPixmap(QColor(206, 216, 226)); });
}

AddIncome::~AddIncome()
{
    delete ui;
}

void AddIncome::changeIncome(QString income)
{
    ui->title->setText("Change Income");

    QString str = QString("You made %1 this month.").arg(income);
    lineEdit->setCustomPlaceholderText(str);
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
    lineEdit->setFrame(false);
    lineEdit->setFixedSize(525, 30);

    ui->lineEditLayout->insertWidget(0, lineEdit);
}

void AddIncome::createBinLabel()
{
    binLabel = new CustomLabel(this);
    binLabel->setFixedSize(30, 30);

    ui->lineEditLayout->insertWidget(1, binLabel);
}

void AddIncome::setBinLabelPixmap(QColor color)
{
    QPixmap px(":/icons/recycle bin.png");
    QPixmap pixmap(px.size());
    pixmap.fill(color);
    pixmap.setMask(px.createMaskFromColor(Qt::transparent));

    binLabel->setPixmap(pixmap);
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

void AddIncome::on_addButton_clicked()
{
    int income = lineEdit->text().toInt();
    QString date = QDate::currentDate().toString("yyyy-MM-dd");
    Database::addIncome(date, income);

    hide();
}
