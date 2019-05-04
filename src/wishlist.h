#ifndef WISHLIST_H
#define WISHLIST_H

#include "paintedwidget.h"
#include "customlineedit.h"
#include "customlabel.h"

namespace Ui {
class WishList;
}

class WishList : public PaintedWidget
{
    Q_OBJECT

public:
    explicit WishList(PaintedWidget *parent = 0);
    ~WishList();

    void clearFocus();
    QVector<CustomLineEdit *> editVec;
    void isBinLabelHidden(bool);
    void emitBinLabelClickedSignal();

private:
    Ui::WishList *ui;
    CustomLabel *binLabel;

    void createNewWishEdit(QString, QLayout *, int width = 480);
    void createTimeEdit();
    void setBinLable();

signals:
    void deleteWishList();
    void lineEditTextEdited();
    void disconnectTextEditSignal();

private slots:
    void changeUnderLineToRed();
    void emitLineEditedSignal();
    void disconnectLineEditSignal();
};

#endif // WISHLIST_H
