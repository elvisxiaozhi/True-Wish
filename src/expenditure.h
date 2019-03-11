#ifndef EXPENDITURE_H
#define EXPENDITURE_H

#include "customwidget.h"

class Expenditure : public CustomWidget
{
    Q_OBJECT
public:
    explicit Expenditure(CustomWidget *parent = nullptr);
    ~Expenditure();

private:
};

#endif // EXPENDITURE_H
