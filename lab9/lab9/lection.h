#pragma once
#include <string>
#include <QVariant>

using std::string;


typedef struct 
{
    int id;
    string title;
    string lectorer;
    int students;
}Lection;

Q_DECLARE_METATYPE(Lection);


