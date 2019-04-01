#ifndef CUSTOMLINEEDIT_H
#define CUSTOMLINEEDIT_H

#include <QLineEdit>
#include <QColor>

class CustomLineEdit : public QLineEdit
{
    Q_OBJECT
public:
    CustomLineEdit(QWidget *parent = nullptr, int distance = 20);
    ~CustomLineEdit();

    void setCustomPlaceholderText(const QString &);
    void setCustomPlaceholderColor(const QColor &);
    void changeFocuseEffect(QWidget *);
    void setInAndExAttr();
    void setWishAttr(QString);

private:
    QString mText;
    QColor color;
    bool focused;
    int paintDistance;

protected:
    void focusInEvent(QFocusEvent *);
    void paintEvent(QPaintEvent *);
    void enterEvent(QEvent *) override;
    void leaveEvent(QEvent *) override;

signals:
    void isFocused(bool);
    void entered();
    void left();

private slots:
    void onFocus(bool);
};

#endif // CUSTOMLINEEDIT_H
