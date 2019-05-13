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

void Database::addWish(QString date, QString wish, int goal, int years, int months, int days)
{
    QSqlQuery query;
    query.prepare("INSERT INTO wishes"
                  "(created_date, wish, fin_goal, years, months, days)"
                  "VALUES"
                  "(:date, :wish, :fin_goal, :years, :months, :days)");
    query.bindValue(":date", date);
    query.bindValue(":wish", wish);
    query.bindValue(":fin_goal", goal);
    query.bindValue(":years", years);
    query.bindValue(":months", months);
    query.bindValue(":days", days);
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

void Database::changeWish(QString wish, int goal, int years, int months, int days, QString origWish, int origGoal)
{
    QSqlQuery query;
    QString str = QString("UPDATE wishes SET wish = '%1', fin_goal = %2, years = %3, months = %4, days = %5"
                          " WHERE wish = '%6' AND fin_goal = %7").arg(wish).arg(goal).arg(years).arg(months).arg(days).arg(origWish).arg(origGoal);
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

QVector<tuple<QString, QString, int, int, int, int> > Database::returnWishInfo()
{
    QVector<tuple<QString, QString, int, int, int, int> > res;

    QSqlQuery query;
    query.prepare("SELECT * FROM wishes");
    query.exec();

    while (query.next())
        res.push_back(make_tuple(query.value(1).toString(), query.value(2).toString(),
                                 query.value(3).toInt(), query.value(4).toInt(),
                                 query.value(5).toInt(), query.value(6).toInt()));

    int i;
    for (i = 0; i < res.size(); ++i) {
        qDebug() << get<0>(res[i]) << get<1>(res[i])
                 << get<2>(res[i]) << get<3>(res[i]) << get<4>(res[i]);
    }

    return res;
}

int Database::countSavedMoney(QString sDate, QString eDate)
{
    int saved, income = 0, expenditure = 0;
    QString str = QString("SELECT * FROM %1 WHERE created_date BETWEEN DATE_SUB('%2', INTERVAL DAY('%2') - 1 DAY) AND LAST_DAY('%3')");

    QSqlQuery query;
    query.prepare(str.arg("income").arg(sDate).arg(eDate));
    query.exec();
    while (query.next()) {
        income += query.value(2).toInt();
    }

    query.prepare(str.arg("expenditure").arg(sDate).arg(eDate));
    query.exec();
    while (query.next()) {
        expenditure += query.value(2).toInt();
    }

    saved = income - expenditure;

    return saved;
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

    return list;
}
