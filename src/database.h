#ifndef DATABASE_H
#define DATABASE_H

#include <QObject>
#include <QSqlDatabase>
#include <QDebug>

class Database : public QObject
{
    Q_OBJECT
public:
    explicit Database(QObject *parent = nullptr);
    ~Database();
    static void addIncome(QString, int);
    static int returnIncome(QString);
    static void modifyData(QString, QString, QString, QString, int, int, int, QString, QString);
    static void deleteRow(QString);

private:
    QSqlDatabase db;
};

#endif // DATABASE_H
