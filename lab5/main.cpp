#pragma once

#include <iostream>
#include <string>

// #include "storage.hpp"
#include "cui.hpp"

using namespace std;
using namespace Csv;

int main(int argc, char *argv[])
{
    
    Storage storage("./data/");
    storage.load();

    Cui cui(&storage);
    cui.show();

    return 0;
}