#ifndef CUSTOMWIDGET_H
#define CUSTOMWIDGET_H

#include "paintedwidget.h"
#include "customlineedit.h"
#include "core/database.h"
#include "customlabel.h"
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

private:
    void createLineEdit();
    void createLine();
    void mousePressEvent(QMouseEvent *) override;

protected:
    Ui::InAndEx *ui;
    CustomLineEdit *lineEdit;

    CustomLabel *createBinLabel();

private slots:
    void on_closeButton_clicked();
};

#endif // CUSTOMWIDGET_H
