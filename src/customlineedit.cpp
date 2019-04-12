#include "customlineedit.h"
#include <QFocusEvent>
#include <QPaintEvent>
#include <QPainter>
#include <QDebug>
#include <QIntValidator>

QString CustomLineEdit::styleString = QString("background-color: #414B66; padding: 10px 2px; font: 20px; color: white;"
                                              "border-style: solid; border-color: #414B66 #414B66 %1 #414B66; border-width: 1px;");

CustomLineEdit::CustomLineEdit(QWidget *parent, int distance)
    : QLineEdit(parent)
{
    paintDistance = distance; //use distance to make placeholder slightly move to the right
    color = QColor(199, 205, 221);
    setFrame(false);
    setStyleSheet(styleString.arg("#BFC6D6"));

    connect(this, &CustomLineEdit::isFocused, this, &CustomLineEdit::onFocus);
}

void CustomLineEdit::setCustomPlaceholderText(const QString &text)
{
    mText = text;
}

void CustomLineEdit::setCustomPlaceholderColor(const QColor &color)
{
    this->color = color;
}

void CustomLineEdit::focusLeft()
{
    connect(this, &CustomLineEdit::left, [this](){
        emit isFocused(false);
    });
}

void CustomLineEdit::setInAndExAttr()
{
    setValidator(new QIntValidator(0, INT_MAX, this));
    setFixedWidth(525);
    setCustomPlaceholderText("How much money did you make this month?");
}

void CustomLineEdit::setWishAttr(QString text)
{
    setCustomPlaceholderText(text);
    setFixedWidth(250);
}

void CustomLineEdit::focusInEvent(QFocusEvent *event)
{
    QLineEdit::focusInEvent(event);   
    emit isFocused(true);
}

//this function is used for hover effects on placeholder text
void CustomLineEdit::paintEvent(QPaintEvent *event)
{
    QLineEdit::paintEvent(event);

    if (text().isEmpty() && !mText.isEmpty()) {
        Q_ASSERT(placeholderText().isEmpty());
        QPainter painter(this);
        painter.setPen(color);
        QFontMetrics fm = fontMetrics();
        int minLB = qMax(0, -fm.minLeftBearing());
        QRect lineRect = this->rect();
        QRect ph = lineRect.adjusted(minLB + paintDistance, 0, 0, 0);
        QString elidedText = fm.elidedText(mText, Qt::ElideRight, ph.width());
        painter.drawText(ph, Qt::AlignVCenter, elidedText);
    }
}

void CustomLineEdit::enterEvent(QEvent *)
{
    color = QColor(255, 255, 255);
    emit entered();
}

void CustomLineEdit::leaveEvent(QEvent *)
{
    if (!focused) {
        color = QColor(199, 205, 221);
    }
    emit left();
}

void CustomLineEdit::onFocus(bool isFocused)
{
    focused = isFocused;

    if (isFocused) {
        color = QColor(255, 255, 255);
        setStyleSheet(styleString.arg("white"));
        emit focusIn(); //focusIn signal is used to make sure that only one placeholder text can be hightlighted
    }
    else {
        color = QColor(199, 205, 221);
        setStyleSheet(styleString.arg("#BFC6D6"));
    }
}
