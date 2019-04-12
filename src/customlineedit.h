#ifndef CUSTOMLINEEDIT_H
#define CUSTOMLINEEDIT_H

#include <QLineEdit>
#include <QColor>

class CustomLineEdit : public QLineEdit
{
    Q_OBJECT
public:
    CustomLineEdit(QWidget *parent = nullptr, int distance = 4);
    void setCustomPlaceholderText(const QString &);
    void setCustomPlaceholderColor(const QColor &);
    void focusLeft();
    void setInAndExAttr();
    void setWishAttr(QString);

private:
    QString mText;
    QColor color;
    bool focused;
    int paintDistance;
    static QString styleString;

protected:
    void focusInEvent(QFocusEvent *);
    void paintEvent(QPaintEvent *);
    void enterEvent(QEvent *);
    void leaveEvent(QEvent *);

signals:
    void isFocused(bool);
    void entered();
    void left();
    void focusIn();

private slots:
    void onFocus(bool);
};

#endif // CUSTOMLINEEDIT_H
