#ifndef EXPENDITURE_H
#define EXPENDITURE_H

#include "inandexwidget.h"

class Expenditure : public InAndExWidget
{
    Q_OBJECT
public:
    explicit Expenditure(InAndExWidget *parent = nullptr);
    ~Expenditure();

    void setAddExpenditureWindow(const QString);
    void setChangeExpenditureWindow(const QString);
    static tuple<QString, int> updateExpenditureInfo(QString);

private:
    static int expenditure;
    static QString expenditureAddedDate;
    CustomLabel *binLabel;

    void setExpenditureButtons();

signals:
    void expenditureAdded();
    void expenditureChanged();
    void expenditureDeleted();

private slots:
    void addExpenditure();
    void changeExpenditure();
    void deleteExpenditure();
};

#endif // EXPENDITURE_H
