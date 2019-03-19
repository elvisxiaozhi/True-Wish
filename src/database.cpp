#include "database.h"
#include <QSqlError>
#include <QSqlQuery>

const QMap<QString, QString> Database::months = {
    {"01", "January"}, {"02", "February"}, {"03", "March"}, {"04", "April"},
    {"05", "May"}, {"06", "June"}, {"07", "July"}, {"08", "August"},
    {"09", "September"}, {"10", "October"}, {"11", "November"}, {"12", "December"}
};

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
    QStringList list = date.split("-");
    QString str = QString("SELECT *FROM income WHERE created_date >= '%1-%2-01' AND created_date <= '%1-%2-31'").arg(list[0]).arg(list[1]);
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
    QStringList list = date.split("-");
    QString str = QString("SELECT *FROM expenditure WHERE created_date >= '%1-%2-01' AND created_date <= '%1-%2-31'").arg(list[0]).arg(list[1]);
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

QStringList Database::returnStoredMonth(QString date)
{
    QStringList list;

    QString str = QString("SELECT * FROM income join expenditure "
                          "WHERE income.created_date >= '%1-01-01' AND income.created_date <= '%1-12-31'"
                          "AND expenditure.created_date >= '%1-01-01 'AND expenditure.created_date <= '%1-12-31';").arg(date);
    QSqlQuery query;
    query.prepare(str);
    query.exec();

    while (query.next()) {
        list.push_back(months.value(QString(query.value(1).toString()).split("-")[1]));
        list.push_back(months.value(QString(query.value(4).toString()).split("-")[1]));
    }

    list = list.toSet().toList();

    return list;
}
