#include <QtSql>
#include "storage.h"
#include <QSqlDatabase>
#include <QSqlQuery>

class SQLiteStorage: public Storage
{
    QSqlDatabase db ;
    const string dir_name_;
    User user;
public:
    SQLiteStorage(const string & dir_name) ;
    ~SQLiteStorage();

    bool open();
    bool close();

    // lections
    vector<Lection> getAllLections(void);
    vector<Lection> getUserLections(int user_id);
    optional<Lection> getLectionById(int lection_id);
    bool updateLection(const Lection &lection);
    bool removeLection(int lection_id);
    int insertLection(const Lection &lection);

    // topics
    vector<Topic> getAllTopics(void);
    optional<Topic> getTopicById(int topic_id);
    bool updateTopic(const Topic &topic);
    bool removeTopic(int topic_id);
    int insertTopic(const Topic &topic);
    // users
    optional<User> getUserAuth(string & username, string & password) ;
    // links
     vector<Topic> getAllLectionTopics(int lection_id) ;
    bool insertLectionTopic(int lection_id, int topic_id) ;
    bool removeLectionTopic(int lection_id, int topic_id) ;
    void setUser(User user) ;
    User getUser() ;
};
