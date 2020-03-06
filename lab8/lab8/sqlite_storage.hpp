#ifndef SQLITE_STORAGE_HPP
#define SQLITE_STORAGE_HPP

#include "storage.hpp"
#include <QtSql>
#include <QSqlDatabase>

class SQlitestorage : public Storage
{
    const string dir_name_;
    QSqlDatabase db_;

public:

    SQlitestorage(const string & dir_name) : dir_name_(dir_name)
    {
        db_ = QSqlDatabase::addDatabase("QSQLITE");
    }



    bool open();
    bool close();
    // lections
    vector<Lection> getAllLections(void);
    optional<Lection> getLectionById(int student_id);
    bool updateLection(const Lection &lection);
    bool removeLection(int lection_id);
    int insertLection(const Lection &lection);
    // courses
    vector<Topic> getAllTopics(void);
    optional<Topic> getTopicById(int topic_id);
    bool updateTopic(const Topic &topic);
    bool removeTopic(int topic_id);
    int insertTopic(const Topic &topic);
};

#endif // SQLITE_STORAGE_HPP
