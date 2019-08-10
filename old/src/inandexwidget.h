#ifndef INANDEXWIDGET_H
#define INANDEXWIDGET_H

#include "paintedwidget.h"
#include "customlineedit.h"
#include "core/database.h"
#include <QDate>

namespace Ui {
class InAndEx;
}

class InAndExWidget : public PaintedWidget
{
    Q_OBJECT

public:
    explicit InAndExWidget(PaintedWidget *parent = nullptr, int width = 600);
    ~InAndExWidget();
    CustomLineEdit *lineEdit;

    void setBinLabelAttr(CustomLabel *);

private:
    void createLineEdit();
    void mousePressEvent(QMouseEvent *) override;

protected:
    Ui::InAndEx *ui;

private slots:
    void on_closeButton_clicked();
};

#endif
