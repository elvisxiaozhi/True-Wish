#ifndef CUSTOMWIDGET_H
#define CUSTOMWIDGET_H

#include <QWidget>
#include <QAction>
#include "customlineedit.h"
#include "database.h"
#include "customlabel.h"
#include <QDate>

namespace Ui {
class InAndEx;
}

class CustomWidget : public QWidget
{
    Q_OBJECT

public:
    explicit CustomWidget(QWidget *parent = nullptr);
    ~CustomWidget();

private:
    QAction *closeAction;
    bool onHover;

    QAction *addAction(const QString &);
    QAction *actionAt(const QPoint &);
    void createLineEdit();
    void createLine();
    void paintEvent(QPaintEvent *);
    void mouseMoveEvent(QMouseEvent *);
    void mousePressEvent(QMouseEvent *);

protected:
    Ui::InAndEx *ui;
    CustomLineEdit *lineEdit;

    CustomLabel *createBinLabel();
    QPixmap returnBinLabelPixmap(QColor);

private slots:
    void on_closeButton_clicked();
};

#endif // CUSTOMWIDGET_H
