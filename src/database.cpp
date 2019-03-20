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
    QString str = QString("SELECT * FROM income WHERE created_date BETWEEN DATE_SUB('%1', INTERVAL DAY('%1') - 1 DAY) AND LAST_DAY('%1')").arg(date);
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
    QString str = QString("SELECT * FROM expenditure WHERE created_date BETWEEN DATE_SUB('%1', INTERVAL DAY('%1') - 1 DAY) AND LAST_DAY('%1')").arg(date);
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
    QString str = QString("SELECT created_date FROM income WHERE created_date BETWEEN '%1-01-01' AND '%1-12-31'"
                          "UNION ALL "
                          "SELECT created_date FROM expenditure WHERE created_date BETWEEN '%1-01-01' AND '%1-12-31';").arg(date);
    QSqlQuery query;
    query.prepare(str);
    query.exec();

    QStringList list;
    while (query.next()) {
        list.push_back(QString(query.value(0).toString()).split("-")[1]);
    }

    std::sort(list.begin(), list.end());
    list.erase(std::unique(list.begin(), list.end()), list.end());
    for (int i = 0; i < list.size(); ++i) {
        list[i] = months.value(list[i]);
    }

    return list;
}
