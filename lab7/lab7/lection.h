#pragma once
#include <string>
#include <QVariant>

using std::string;

struct Lection
{
    int id;
    string title;
    string lectorer;
    int students;
};

Q_DECLARE_METATYPE(Lection);

