#include <QCoreApplication>

#pragma once

#include <iostream>
#include <string>

#include <QDebug>

#include "cui.hpp"
#include "sqlite_storage.hpp"

using namespace std;
using namespace Csv;

void xmlWorking ();
void csvWorking ();
void sqlWorking ();

int main()
{
    int choose;
    cout << "Enter [1] - XML" << endl << "Enter [2] - CSV" << endl << "Enter [3] - SQL" << endl << "EXIT - ANOTHER NUMBER" << endl << "Your choose is ";
    cin >> choose;
    if (choose == 1)
        xmlWorking();
    if (choose == 2)
        csvWorking();
    if (choose == 3)
        sqlWorking();

    return 0;
}

void xmlWorking (){
    XmlStorage xml_storage("../lab8/data/xml");
    Storage * storage_ptr = &xml_storage;
    storage_ptr->open();
    Cui cui(storage_ptr);
    cui.show();
}

void csvWorking (){
    CsvStorage csv_storage("../lab8/data/csv");
    Storage * storage_ptr = &csv_storage;
    storage_ptr->open();
    Cui cui(storage_ptr);
    cui.show();
}

void sqlWorking (){
    SQlitestorage sql_storage("../lab8/data/sql");
    Storage * storage_ptr = &sql_storage;
    storage_ptr->open();
    Cui cui(storage_ptr);
    cui.show();
}
