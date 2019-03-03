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

protected:
    virtual void focusInEvent(QFocusEvent *);
    void paintEvent(QPaintEvent *);

signals:
    void isFocused(bool);

private slots:
    void onFocus(bool);
};

#endif // CUSTOMLINEEDIT_H
