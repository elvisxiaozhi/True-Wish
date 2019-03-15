#include "database.h"
#include <QSqlError>
#include <QSqlQuery>
#include <QDate>

Database::Database(QObject *parent) : QObject(parent)
{
    db = QSqlDatabase::addDatabase("QMYSQL");
    db.setHostName("localhost");
    db.setDatabaseName("test");
    db.setUserName("root");
    db.setPassword("password");

    if(!db.open()) {
        qDebug() << db.lastError();
    }
}

Database::~Database()
{
    db.close();
}

void Database::addIncome(QString date, int income)
{
    QSqlQuery query;
    query.prepare("INSERT INTO income"
                  "(created_date, income)"
                  "VALUES"
                  "(:date, :income)");
    query.bindValue(":date", date);
    query.bindValue(":income", income);
    query.exec();
}

void Database::addExpenditure(QString date, int expenditure)
{
    QSqlQuery query;
    query.prepare("INSERT INTO expenditure"
                  "(created_date, expenditure)"
                  "VALUES"
                  "(:date, :expenditure)");
    query.bindValue(":date", date);
    query.bindValue(":expenditure", expenditure);
    query.exec();
}

void Database::changeIncome(QString date, int income)
{
    QSqlQuery query;
    QString str = QString("UPDATE income SET income = %1 WHERE created_date = '%2'").arg(income).arg(date);
    query.prepare(str);
    query.exec();
}

void Database::changeExpenditure(QString date, int expenditure)
{
    QSqlQuery query;
    QString str = QString("UPDATE expenditure SET expenditure = %1 WHERE created_date = '%2'").arg(expenditure).arg(date);
    query.prepare(str);
    query.exec();
}

tuple<QString, int> Database::returnIncomeInfo(QString date)
{
    QString str = QString("SELECT *FROM income WHERE created_date >= '%1-01-01'").arg(date);
    QSqlQuery query;
    query.prepare(str);
    query.exec();

    if (query.next()) {
        return make_tuple(query.value(1).toString(), query.value(2).toInt());
    }

    return make_tuple("", 0);
}

tuple<QString, int> Database::returnExpenditureInfo(QString date)
{
    QString str = QString("SELECT *FROM expenditure WHERE created_date >= '%1-01-01'").arg(date);
    QSqlQuery query;
    query.prepare(str);
    query.exec();

    if (query.next()) {
        return make_tuple(query.value(1).toString(), query.value(2).toInt());
    }

    return make_tuple("", 0);
}

void Database::deleteIncome(QString date)
{
    QSqlQuery query;
    QString str = QString("DELETE FROM income WHERE created_date = '%1'").arg(date);
    query.prepare(str);
    query.exec();
}

void Database::deleteExpendture(QString date)
{
    QSqlQuery query;
    QString str = QString("DELETE FROM expenditure WHERE created_date = '%1'").arg(date);
    query.prepare(str);
    query.exec();
}

QStringList Database::returnStoredMonth()
{
    QStringList list;

    QString str = QString("SELECT * FROM income join expenditure WHERE income.created_date >= '2019-01-01' AND expenditure.created_date >= '2019-01-01';");
    QSqlQuery query;
    query.prepare(str);
    query.exec();

    while (query.next()) {
        list.push_back(QDate::fromString(query.value(1).toString(), "yyyy-MM-dd").toString("MMMM"));
        list.push_back(QDate::fromString(query.value(4).toString(), "yyyy-MM-dd").toString("MMMM"));
    }

    list = list.toSet().toList();

    return list;
}
