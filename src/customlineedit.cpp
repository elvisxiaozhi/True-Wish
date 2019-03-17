#include "customlineedit.h"
#include <QFocusEvent>
#include <QPaintEvent>
#include <QPainter>
#include <QDebug>
#include <QIntValidator>

CustomLineEdit::CustomLineEdit(QWidget *parent, int distance)
    : QLineEdit(parent)
{
    paintDistance = distance;
    color = QColor(199, 205, 221);
    setValidator(new QIntValidator(0, INT_MAX, this));
    setFrame(false);

    connect(this, &CustomLineEdit::isFocused, this, &CustomLineEdit::onFocus);
}

CustomLineEdit::~CustomLineEdit()
{
}

void CustomLineEdit::setCustomPlaceholderText(const QString &text)
{
    mText = text;
}

void CustomLineEdit::setCustomPlaceholderColor(const QColor &color)
{
    this->color = color;
}

void CustomLineEdit::setInAndExAttr()
{
    setFixedSize(525, 30);
    setCustomPlaceholderText("How much money did you make this month?");
    setStyleSheet("background-color: #414B66; padding: 0px 19px; font: 20px; border: none; color: white;");
}

void CustomLineEdit::focusInEvent(QFocusEvent *event)
{
    QLineEdit::focusInEvent(event);
    emit isFocused(true);
}

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
    }
    else {
        color = QColor(199, 205, 221);
    }
}
