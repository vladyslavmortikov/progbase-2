#include <QCoreApplication>

#pragma once

#include <iostream>
#include <string>

#include <QDebug>

#include "cui.hpp"

using namespace std;
using namespace Csv;

int main()
{
    int choose;
    cout << "Enter [1] - XML" << endl << "Enter [2] - CSV" << endl << "EXIT - ANOTHER NUMBER" << endl << "Your choose is ";
    cin >> choose;
    Storage * storage_ptr = nullptr;
    if (choose == 1)
    {
        XmlStorage * xml_storage = new XmlStorage("../lab6v1/data/xml");
        storage_ptr = xml_storage;
    } else if (choose == 2)
    {
         CsvStorage * csv_storage = new CsvStorage("../lab6v1/data/csv");
         storage_ptr = csv_storage;
    } else {
        return 1;
    }

    storage_ptr->load();
    Cui cui(storage_ptr);
    cui.show();

    delete storage_ptr;

    return 0;
}
