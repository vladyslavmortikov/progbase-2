#include "sqlite_storage.hpp"
#include <QtSql>
#include <iostream>
#include <QDebug>

//SQlitestorage::SqliteStorage(const string &dir_name): dir_name_(dir_name)
//{
//    db_ = QSqlDatabase::addDatabase("QSQLITE");
//}

bool SQlitestorage::open()
{
    QString path = QString::fromStdString(this->dir_name_) + "/data.sqlite";
    db_.setDatabaseName(path);
    bool connected = db_.open();
    if (!connected) {return false;}
    return true;
}

bool SQlitestorage::close()
{
    db_.close();
    return true;
}

vector<Lection> SQlitestorage::getAllLections(void)
{
    vector<Lection> lections;
    QSqlQuery query("SELECT * FROM lections");

    if (!query.exec()) {
        qDebug() << "getAlllections error:" << query.lastError().text();
    }

    while (query.next())
    {
        Lection newLection;
        newLection.id = query.value("id").toInt();
        newLection.title = query.value("title").toString().toStdString();
        newLection.lectorer = query.value("lectorer").toString().toStdString();
        newLection.students = query.value("students").toInt();

        lections.push_back(newLection);
    }
    return lections;
}

optional<Lection> SQlitestorage::getLectionById(int lection_id)
{
    QSqlQuery query;
    query.prepare("SELECT * FROM lections WHERE id = :id");
    query.bindValue(":id", lection_id);
    if (!query.exec())
    {
        qDebug() << "getLections error:" << query.lastError();
        return nullopt;
    }
    if (query.next())
    {
        Lection newLection;
        newLection.id = query.value("id").toInt();
        newLection.title = query.value("title").toString().toStdString();
        newLection.lectorer = query.value("lectorer").toString().toStdString();
        newLection.students = query.value("students").toInt();
        return newLection;
    }
    else
    {
        return nullopt;
    }
}

bool SQlitestorage::updateLection(const Lection &lection)
{
    QSqlQuery query;
    query.prepare("UPDATE lections SET title = :title, lectorer = :lectorer, students = :students WHERE id = :id");
    query.bindValue(":title", QString::fromStdString(lection.title));
    query.bindValue(":lectorer", QString::fromStdString(lection.lectorer));
    query.bindValue(":students", lection.students);
    query.bindValue(":id", lection.id);
    if (!query.exec()){
        qDebug() << "updateLection error:" << query.lastError();
        return false;
    }
    return true;
}

bool SQlitestorage::removeLection(int lection_id)
{
    QSqlQuery query;
    query.prepare("DELETE FROM lection WHERE id = :id");
    query.bindValue(":id", lection_id);
    if (!query.exec()){
        qDebug() << "removeLection error:" << query.lastError();
        return false;
    }
    if(query.numRowsAffected() == 0)
    {
        return false;
    }
    return true;
}

int SQlitestorage::insertLection(const Lection &lection)
{
    QSqlQuery query;
    query.prepare("INSERT INTO lections (title, lectorer, students)"
                  "VALUES (:title, :lectorer, :students)");
    query.bindValue(":title", QString::fromStdString(lection.title));
    query.bindValue(":lectorer", QString::fromStdString(lection.lectorer));
    query.bindValue(":students", lection.students);
    if (!query.exec()){
        qDebug() << "insertLection error:" << query.lastError();
        return 0;
    }
    QVariant var = query.lastInsertId();
    return var.toInt();
}

vector<Topic> SQlitestorage::getAllTopics(void)
{
    vector<Topic> topics;
    QSqlQuery query("SELECT * FROM topics");

    if (!query.exec()) {
        qDebug() << "getAllTopics error:" << query.lastError().text();
    }

    while (query.next())
    {
        Topic newTopic;
        newTopic.id = query.value("id").toInt();
        newTopic.data = query.value("data").toString().toStdString();
        newTopic.topic = query.value("topic").toString().toStdString();
        newTopic.students = query.value("students").toInt();
        topics.push_back(newTopic);
    }
    return topics;
}

optional<Topic> SQlitestorage::getTopicById(int topic_id)
{
    QSqlQuery query;
    query.prepare("SELECT * FROM topics WHERE id = :id");
    query.bindValue(":id", topic_id);
    if (!query.exec())
    {
        qDebug() << "getTopicById error:" << query.lastError();
        return nullopt;
    }
    if (query.next())
    {
        Topic newTopic;
        newTopic.id = query.value("id").toInt();
        newTopic.data = query.value("data").toString().toStdString();
        newTopic.topic = query.value("topic").toString().toStdString();
        newTopic.students = query.value("students").toInt();
        return newTopic;
    }
    else
    {
        return nullopt;
    }
}

bool SQlitestorage::updateTopic(const Topic &topic)
{
    QSqlQuery query;
    query.prepare("UPDATE topics SET data = :data, topic = :topic, students = :students WHERE id = :id");
    query.bindValue(":data", QString::fromStdString(topic.data));
    query.bindValue(":topic", QString::fromStdString(topic.topic));
    query.bindValue(":students",topic.students);
    query.bindValue(":id", topic.id);

    if (!query.exec()){
        qDebug() << "updateTopic error:" << query.lastError();
        return false;
    }
    return true;

}

bool SQlitestorage::removeTopic(int topic_id)
{
    QSqlQuery query;
    query.prepare("DELETE FROM topics WHERE id = :id");
    query.bindValue(":id", topic_id);
    if (!query.exec()){
        qDebug() << "removeTopic error:" << query.lastError();
        return false;
    }
    if(query.numRowsAffected() == 0)
    {
        return false;
    }
    return true;
}

int SQlitestorage::insertTopic(const Topic &topic)
{
    QSqlQuery query;
    query.prepare("INSERT INTO topics (data, topic, students) VALUES (:data, :topic, :students)");
    query.bindValue(":data", QString::fromStdString(topic.data));
    query.bindValue(":topic", QString::fromStdString(topic.topic));
    query.bindValue(":students", topic.students);
    if (!query.exec()){
        qDebug() << "insertTopic error:" << query.lastError();
        return 0;
    }
    QVariant var = query.lastInsertId();
    return var.toInt();
}
