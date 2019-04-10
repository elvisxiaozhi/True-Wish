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

private:
    Ui::WishList *ui;
    CustomLineEdit *wishEdit, *goalEdit, *timeEdit;

    void createWishEdit();
    void createGoalEdit();
    void createTimeEdit();
};

#endif // WISHLIST_H
