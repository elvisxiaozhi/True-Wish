#ifndef WISHLIST_H
#define WISHLIST_H

#include <QWidget>
#include "customlineedit.h"

namespace Ui {
class WishList;
}

class WishList : public QWidget
{
    Q_OBJECT

public:
    explicit WishList(QWidget *parent = 0);
    ~WishList();

    void clearFocus();

private:
    Ui::WishList *ui;
    CustomLineEdit *wishEdit, *goalEdit, *timeEdit;

    void createWishEdit();
    void createGoalEdit();
    void createTimeEdit();
};

#endif // WISHLIST_H
