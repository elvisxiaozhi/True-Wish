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
    void setWishAttr(QString, int width = 480);
    static QString styleString;

private:
    QString mText;
    QColor color;
    bool focused;
    int paintDistance;

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
    void changeUnderLineToRed();

private slots:
    void onFocus(bool);
};

#endif // CUSTOMLINEEDIT_H
