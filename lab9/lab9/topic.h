#pragma once
#include <string>
#include <QVariant>
using std::string;

typedef struct 
{
    int id;
    string data;
    string topic;
    int students;
}Topic;

Q_DECLARE_METATYPE(Topic);
