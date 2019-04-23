#ifndef DATABASE_H
#define DATABASE_H

#include <QObject>
#include <QSqlDatabase>
#include <QDebug>
#include <QMap>

using std::tuple;
using std::make_tuple;
using std::tie;
using std::get;

class Database : public QObject
{
    Q_OBJECT
public:
    explicit Database(QObject *parent = nullptr);
    ~Database();
    static const QMap<QString, QString> months;
    static void addIncome(QString, int);
    static void addExpenditure(QString, int);
    static void addWish(QString, QString, int, int, int, int);
    static void changeIncome(QString, int);
    static void changeExpenditure(QString, int);
    static void changeWish(QString, int, int, int, int, QString, int);
    static tuple<QString, int> returnIncomeInfo(QString);
    static tuple<QString, int> returnExpenditureInfo(QString);
    static QVector<tuple<QString, QString, int, int, int, int> > returnWishInfo();
    static void deleteIncome(QString);
    static void deleteExpendture(QString);
    static QStringList returnStoredMonth(QString);

private:
    QSqlDatabase db;
};

#endif // DATABASE_H
