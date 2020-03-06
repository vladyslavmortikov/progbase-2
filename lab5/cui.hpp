#include <iostream>
#include <cstdlib>

#include "storage.hpp"

using namespace std;

class Cui
{
    Storage *const storage_;

    // lections menus
    void lectionsMainMenu();
    void lectionMenu(int entity_id);
    void lectionUpdateMenu(int entity_id);
    void lectionDeleteMenu(int entity_id);
    void lectionCreateMenu();
    void printLection(vector<Lection> &lec);

    // topics menus
    void topicsMainMenu();
    void topicMenu(int entity_id);
    void topicUpdateMenu(int entity_id);
    void topicDeleteMenu(int entity_id);
    void topicCreateMenu();
    void printTopics(vector<Topic> &top);

public:
    Cui(Storage *storage) : storage_(storage) {}

    void show();
};