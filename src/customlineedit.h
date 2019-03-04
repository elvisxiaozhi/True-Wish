#ifndef CUSTOMLINEEDIT_H
#define CUSTOMLINEEDIT_H

#include <QLineEdit>
#include <QColor>

class CustomLineEdit : public QLineEdit
{
    Q_OBJECT
public:
    CustomLineEdit(QWidget *parent = nullptr);
    ~CustomLineEdit();

    void setCustomPlaceholderText(const QString &);
    void setCustomPlaceholderColor(const QColor &);

private:
    QString mText;
    QColor color;
    bool focused;

protected:
    void focusInEvent(QFocusEvent *);
    void paintEvent(QPaintEvent *);
    void enterEvent(QEvent *) override;
    void leaveEvent(QEvent *) override;

signals:
    void isFocused(bool);

private slots:
    void onFocus(bool);
};

#endif // CUSTOMLINEEDIT_H
