#include "database.h"
#include <QSqlError>
#include <QSqlQuery>

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

void Database::changeIncome(QString date, int income)
{
    QSqlQuery query;
    QString str = QString("UPDATE income SET income = %1 WHERE created_date = '%2'").arg(income).arg(date);
    qDebug() << str;
    query.prepare(str);
    query.exec();
}

tuple<QString, int> Database::returnIncomeInfo(QString date)
{
    QString str = QString("SELECT *FROM income WHERE created_date LIKE '%1-%'").arg(date);
    QSqlQuery query;
    query.prepare(str);
    query.exec();

    if (query.next()) {
        return make_tuple(query.value(1).toString(), query.value(2).toInt());
    }

    return make_tuple("", 0);
}

void Database::modifyData(QString id, QString date, QString title, QString link, int views, int likes, int comments, QString keywords, QString remark)
{
    QSqlQuery query;

    query.prepare("UPDATE articles SET "
                  "publication_date = :dateValue, title = :titleValue, link = :linkValue,"
                  "views = :viewsValue, likes = :likesValue, comments = :commentsValue,"
                  "keywords = :keywordsValue, remark = :remarkValue "
                  "WHERE article_id = :id;");
    query.bindValue(":dateValue", date);
    query.bindValue(":titleValue", title);
    query.bindValue(":linkValue", link);
    query.bindValue(":viewsValue", views);
    query.bindValue(":likesValue", likes);
    query.bindValue(":commentsValue", comments);
    query.bindValue(":keywordsValue", keywords);
    query.bindValue(":remarkValue", remark);
    query.bindValue(":id", id);
    query.exec();
}

void Database::deleteRow(QString id)
{
    QSqlQuery query;
    query.prepare("DELETE FROM articles WHERE article_id = :id");
    query.bindValue(":id", id);
    query.exec();
}
