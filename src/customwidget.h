#ifndef CUSTOMWIDGET_H
#define CUSTOMWIDGET_H

#include "paintedwidget.h"
#include "customlineedit.h"
#include "core/database.h"
#include <QDate>

namespace Ui {
class InAndEx;
}

class CustomWidget : public PaintedWidget
{
    Q_OBJECT

public:
    explicit CustomWidget(PaintedWidget *parent = nullptr, int width = 600);
    ~CustomWidget();
    CustomLineEdit *lineEdit;

    void setBinLabelAttr(CustomLabel *);

private:
    void createLineEdit();
    void createLine();
    void mousePressEvent(QMouseEvent *) override;

protected:
    Ui::InAndEx *ui;

private slots:
    void on_closeButton_clicked();
};

#endif // CUSTOMWIDGET_H
