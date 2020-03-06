#include "sqlite_storage.h"
#include <QtSql>
#include <QDebug>

void SQLiteStorage::setUser(User user) {
    this->user=user;
}
User SQLiteStorage::getUser() {
    return user;
}


vector<Lection> SQLiteStorage::getUserLections(int user_id){
    vector <Lection> lections;
    QSqlQuery query;
    query.prepare("SELECT * FROM lections WHERE user_id=:user_id");
    query.bindValue(":user_id",user_id);
    if (!query.exec()) {
        qDebug() << "getLections error:" << query.lastError();
        return lections;
    }
    while (query.next())
    {
        Lection lec;
        lec.id=query.value("id").toInt();
        lec.title = query.value("title").toString().toStdString();
        lec.lectorer=query.value("lectorer").toString().toStdString();
        lec.students=query.value("students").toInt();
        lections.push_back(lec);
    }
    return lections;
}

vector<Topic> SQLiteStorage::getAllLectionTopics(int lection_id) {
    vector<Topic> topics;
    QSqlQuery query;
    query.prepare("SELECT * FROM links WHERE lection_id=:lection_id");
    query.bindValue(":lection_id",lection_id);
    if (!query.exec()) {
        qDebug() << "getTopics error:" << query.lastError();
        return topics;
    }
    while (query.next()){
        topics.push_back(getTopicById(query.value("topic_id").toInt()).value());
    }
    return topics;
}

bool SQLiteStorage::insertLectionTopic(int lection_id, int topic_id) {
    QSqlQuery query;
    query.prepare("INSERT INTO links (lection_id,topic_id) VALUES (:lection_id,:topic_id)");
    query.bindValue(":lection_id",lection_id);
    query.bindValue(":topic_id",topic_id);
    if (!query.exec()){
        qDebug()<<"qquery error"
               <<query.lastError();
        return false;
    }
    return true;
}

bool SQLiteStorage::removeLectionTopic(int lection_id, int topic_id) {
    QSqlQuery query;
    query.prepare("DELETE FROM links WHERE lection_id = :lection_id AND topic_id=:topic_id");
    query.bindValue(":lection_id",lection_id);
    query.bindValue(":topic_id",topic_id);
    if (!query.exec())
        qDebug()<<"no such";
    return false;
    if (!query.numRowsAffected()){
        qDebug()<<"no such link";
        return false;

    }
    return true;
}

SQLiteStorage::SQLiteStorage(const string & dir_name) : dir_name_(dir_name){
    db=QSqlDatabase::addDatabase("QSQLITE");
}

SQLiteStorage::~SQLiteStorage() {
}

bool SQLiteStorage::open(){
    ifstream file;
    file.open(this->dir_name_+"/data.sqlite");
    if(!file)
        return 0;

    db.setDatabaseName(QString::fromStdString(this->dir_name_)+"/data.sqlite");
    bool connected = db.open();  // open db connection
    if (!connected) {
        db.close();
        return false;
    }
    QSqlQuery query(db);
    query.prepare("PRAGMA foreign_keys = ON");
    return true;
}

bool SQLiteStorage::close(){
    db.close();
    return true;
}

optional<User> SQLiteStorage::getUserAuth(string & username, string & password) {
    User user;
    QSqlQuery query;
    query.prepare("SELECT * FROM users WHERE username = :username AND password_hash=:password ");
    query.bindValue(":username",QString::fromStdString(username));
    QString hash = QString(QCryptographicHash::hash((password.c_str()),QCryptographicHash::Md5).toHex());
    query.bindValue(":password",hash);
    if (!query.exec()) {  // do exec if query is prepared SELECT query
        return nullopt;
    }
    if (query.next()) {
        user.user_id=query.value("id").toInt();
        user.username=query.value("username").toString().toStdString();
        return user;
    } else {
        return nullopt;
    }
}

vector<Lection> SQLiteStorage::getAllLections(void)
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

optional<Lection> SQLiteStorage::getLectionById(int lection_id)
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

bool SQLiteStorage::updateLection(const Lection &lection)
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

bool SQLiteStorage::removeLection(int lection_id)
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

int SQLiteStorage::insertLection(const Lection &lection)
{
    QSqlQuery query;
    query.prepare("INSERT INTO lections (title, lectorer, students, user_id)"
                  "VALUES (:title, :lectorer, :students, :user_id)");
    query.bindValue(":title", QString::fromStdString(lection.title));
    query.bindValue(":lectorer", QString::fromStdString(lection.lectorer));
    query.bindValue(":students", lection.students);
    query.bindValue(":user_id", this->user.user_id);

    if (!query.exec()){
        qDebug() << "insertLection error:" << query.lastError();
        return 0;
    }
    QVariant var = query.lastInsertId();
    return var.toInt();
}

vector<Topic> SQLiteStorage::getAllTopics(void)
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

optional<Topic> SQLiteStorage::getTopicById(int topic_id)
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

bool SQLiteStorage::updateTopic(const Topic &topic)
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

bool SQLiteStorage::removeTopic(int topic_id)
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

int SQLiteStorage::insertTopic(const Topic &topic)
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
