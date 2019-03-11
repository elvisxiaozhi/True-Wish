#ifndef CUSTOMWIDGET_H
#define CUSTOMWIDGET_H

#include <QWidget>
#include <QAction>
#include "customlineedit.h"
#include "customlabel.h"

namespace Ui {
class InAndEx;
}

class CustomWidget : public QWidget
{
    Q_OBJECT

private:
    explicit CustomWidget(QWidget *parent = nullptr);
    ~CustomWidget();

    Ui::InAndEx *ui;
    QAction *closetAction;
    bool onHover;
    CustomLineEdit *lineEdit;
    CustomLabel *binLabel;

    QAction *addAction(const QString &);
    QAction *actionAt(const QPoint &);
    void createLineEdit();
    void createBinLabel();
    void createLine();
    void setBinLabelPixmap(QColor);
    void paintEvent(QPaintEvent *);
    void mouseMoveEvent(QMouseEvent *);
    void mousePressEvent(QMouseEvent *);
};

#endif // CUSTOMWIDGET_H
