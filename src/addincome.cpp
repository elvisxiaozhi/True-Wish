#include "addincome.h"
#include "ui_addincome.h"
#include <QPaintEvent>
#include <QPainter>
#include <QDebug>
#include <windows.h>
#include <QWindow>
#include <QBitmap>

int AddIncome::income;
QString AddIncome::incomeAddedDate;

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
}

AddIncome::~AddIncome()
{
    delete ui;
}

void AddIncome::changeIncome()
{
    ui->title->setText("Change Income");
    ui->addButton->hide();
    ui->modifyButton->show();
    binLabel->show();

    QString str = QString("You made %1 this month.").arg(income);
    lineEdit->setCustomPlaceholderText(str);
}

void AddIncome::addIncome()
{
    ui->title->setText("Add Income");
    ui->addButton->show();
    ui->modifyButton->hide();
    binLabel->hide();
    lineEdit->setCustomPlaceholderText("How much money did you make this month?");
}

void AddIncome::updateIncomeInfo()
{
    tie(incomeAddedDate, income) = Database::returnIncomeInfo(QDate::currentDate().toString("yyyy-MM"));
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

    connect(lineEdit, &CustomLineEdit::entered, [this](){ setBinLabelPixmap(QColor(206, 216, 226)); });
    connect(lineEdit, &CustomLineEdit::left, [this](){ binLabel->setPixmap(QPixmap()); });
}

void AddIncome::createBinLabel()
{
    binLabel = new CustomLabel(this);
    binLabel->setFixedSize(30, 30);

    ui->lineEditLayout->insertWidget(1, binLabel);

    connect(binLabel, &CustomLabel::clicked, this, &AddIncome::deleteIncome);
    connect(binLabel, &CustomLabel::entered, [this](){ setBinLabelPixmap(QColor(255, 255, 255)); });
    connect(binLabel, &CustomLabel::left, [this](){ binLabel->setPixmap(QPixmap()); });
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
    Database::addIncome(QDate::currentDate().toString("yyyy-MM-dd"), lineEdit->text().toInt());
    lineEdit->setText(QString(""));  //clear line edit text after modify button is clicked, clear function is not working here
    hide();

    emit incomeAdded();
}

void AddIncome::on_modifyButton_clicked()
{
    Database::changeIncome(incomeAddedDate, lineEdit->text().toInt());
    lineEdit->setText(QString(""));
    hide();

    emit incomeChanged();
}

void AddIncome::deleteIncome()
{
    Database::deleteIncome(incomeAddedDate);
    hide();

    emit incomeDeleted();
}
