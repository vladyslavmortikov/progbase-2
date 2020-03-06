#include "cui.hpp"

void Cui::show()
{
    system("clear");

    int choose;
    cout << "Please, choose an entity:" << endl
         << endl
         << "\n\t [1] - Lections \n\t [2] - Topics \n\n\t [3] - EXIT" << endl;

    cin >> choose;

    if (choose == 1)
        lectionsMainMenu();
    else if (choose == 2)
        topicsMainMenu();
    else if (choose == 3)
    {
        system("clear");
        int out;
        cout << "ENTER 1 TO SAVE ALL CHANGES or any other number not to save changes" << endl;
        cin >> out;
        if (out == 1)
            storage_->save();
        exit(0);
    }
}

void Cui::lectionsMainMenu()
{
    system("clear");

    int choose;
    cout << "Please, choose an option:"
         << "\n\t[1] - Show all lections\n\t[2] - Update lection\n\t[3] - Delete lection\n\t[4] - Add lection\n\t[5] - Check detailed info\n\t[6] - Go to previos menu" << endl;
    cin >> choose;
    if (choose == 1)
    {
        system("clear");

        for (Lection lec : storage_->getAllLections())
        {
            cout << lec.id << "  " << lec.title << endl;
        }

        cout << "Enter any number to go back here: ";
        cin >> choose;
        lectionsMainMenu();
    }
    else if (choose == 2)
    {
        cout << "\nEnter the lection's id:\n";
        int id;
        cin >> id;
        lectionUpdateMenu(id);
    }
    else if (choose == 3)
    {
        cout << "\nEnter the lection's id:\n";
        int id;
        cin >> id;
        lectionDeleteMenu(id);
    }
    else if (choose == 4)
    {
        lectionCreateMenu();
    }
    else if (choose == 5)
    {
        cout << "\nEnter the lection's id:\n";
        int id;
        cin >> id;
        lectionMenu(id);
    }
    else if (choose == 6)
    {
        show();
    }
    else
    {
        cout << "\nIncorrect input";
        exit(1);
    }
}

void Cui::printLection(vector<Lection> &lec)
{
    for (Lection &lec : lec)
    {
        cout << lec.id << "  ";
        cout << lec.title.c_str() << "  ";
        cout << lec.lectorer.c_str() << "  ";
        cout << lec.students << endl;
    }
}

void Cui::lectionMenu(int entity_id)
{
    system("clear");

    if (!storage_->getLectionById(entity_id))
    {
        cout << "No lection with id" << endl;
    }
    else
    {
        optional<Lection> lec_opt = storage_->getLectionById(entity_id);
        Lection lec = lec_opt.value();
        cout << "The info for the lection with id [" << entity_id << "]" << endl;
        cout << "The title of course is " << lec.title << endl;
        cout << "The lectorer`s name is " << lec.lectorer << endl;
        cout << "The number of students on the course is " << lec.students << endl;
    }

    cout << endl
         << "Enter any number to back to previous menu" << endl;
    int out;
    cin >> out;
    lectionsMainMenu();
}

void Cui::lectionUpdateMenu(int entity_id)
{

    system("clear");

    Lection lec;

    lec.id = entity_id;

    cout << "\t\tLection update menu\n\n Enter new course`s title: ";
    cin >> lec.title;

    cout << "Enter lectorer`s name: ";
    cin >> lec.lectorer;

    cout << "Enter students on the course: ";
    cin >> lec.students;

    if (storage_->updateLection(lec))
        cout << "Succesfully updated! :)";
    else
    {
        cout << "No lection with id " << entity_id;
    }

    cout << "\n\nEnter any value to back to previous menu" << endl;

    char c;
    cin >> c;
    lectionsMainMenu();
}

void Cui::lectionDeleteMenu(int entity_id)
{
    system("clear");

    if (storage_->removeLection(entity_id))
        cout << "\nLection with id " << entity_id << "was deleted";
    else
        cout << "No lection with id " << entity_id;
    cout << "\n\nEnter any value to back to previous menu\n";
    char c;
    cin >> c;
    lectionsMainMenu();
}

void Cui::lectionCreateMenu()
{
    system("clear");

    Lection lec;

    cout << "\t\tLection create menu\n\nEnter new topic: ";
    cin >> lec.title;

    cout << "Enter a lectorer`s name: ";
    cin >> lec.lectorer;

    cout << "Enter number of students: ";
    cin >> lec.students;

    lec.id = storage_->insertLection(lec);
    cout << "\n Lection course created, id = " << lec.id << endl;

    cout << "\n\nenter any value to back to previous menu\n";
    char c;
    cin >> c;
    lectionsMainMenu();
}

void Cui::topicsMainMenu()
{
    system("clear");

    int choose;
    cout << "Please, choose an option:"
         << "\n\t[1] - Show all topics\n\t[2] - Update topic\n\t[3] - Delete topic\n\t[4] - Add topic\n\t[5] - Check detailed info\n\t[6] - Go to previos menu" << endl;
    cin >> choose;
    if (choose == 1)
    {
        system("clear");

        for (Topic top : storage_->getAllTopics())
        {
            cout << top.id << "  " << top.topic << endl;
        }

        cout << "Enter any number to go back here: ";
        cin >> choose;
        topicsMainMenu();
    }
    else if (choose == 2)
    {
        cout << "\nEnter the topic's id:\n";
        int id;
        cin >> id;
        topicUpdateMenu(id);
    }
    else if (choose == 3)
    {
        cout << "\nEnter the topic's id:\n";
        int id;
        cin >> id;
        topicDeleteMenu(id);
    }
    else if (choose == 4)
    {
        topicCreateMenu();
    }
    else if (choose == 5)
    {
        cout << "\nEnter the topic's id:\n";
        int id;
        cin >> id;
        topicMenu(id);
    }
    else if (choose == 6)
    {
        show();
    }
    else
    {
        cout << "\nIncorrect input";
        exit(1);
    }
}

void Cui::printTopics(vector<Topic> &top)
{
    for (Topic &top : top)
    {
        cout << top.id << "  ";
        cout << top.data.c_str() << "  ";
        cout << top.topic.c_str() << "  ";
        cout << top.students << endl;
    }
}

void Cui::topicMenu(int entity_id)
{
    system("clear");

    if (!storage_->getTopicById(entity_id))
    {
        cout << "No topic with id" << endl;
    }
    else
    {
        optional<Topic> top_opt = storage_->getTopicById(entity_id);
        Topic top = top_opt.value();
        cout << "The info for the topic with id [" << entity_id << "]" << endl;
        cout << "The lection`s data is " << top.data << endl;
        cout << "The lection`s topic is " << top.topic << endl;
        cout << "The number of students on the lection was " << top.students << endl;
    }

    cout << endl
         << "Enter any number to back to previous menu" << endl;
    int out;
    cin >> out;
    topicsMainMenu();
}

void Cui::topicUpdateMenu(int entity_id)
{

    system("clear");

    Topic top;

    top.id = entity_id;

    cout << "\t\tTopic update menu\n\n Enter new lection`s data: ";
    cin >> top.data;

    cout << "Enter lection`s topic: ";
    cin >> top.topic;

    cout << "Enter students on the lections: ";
    cin >> top.students;

    if (storage_->updateTopic(top))
        cout << "Succesfully updated! :)";
    else
    {
        cout << "No topic with id " << entity_id;
    }

    cout << "\n\nEnter any value to back to previous menu" << endl;

    char c;
    cin >> c;
    topicsMainMenu();
}

void Cui::topicDeleteMenu(int entity_id)
{
    system("clear");

    if (storage_->removeTopic(entity_id))
        cout << "\nTopic with id " << entity_id << "was deleted";
    else
        cout << "No Topic with id " << entity_id;
    cout << "\n\nEnter any value to back to previous menu\n";

    char c;
    cin >> c;
    topicsMainMenu();
}

void Cui::topicCreateMenu()
{
    system("clear");

    Topic top;

    cout << "\t\tTopic create menu\n\nEnter new data: ";
    cin >> top.data;

    cout << "Enter a topic of lection: ";
    cin >> top.topic;

    cout << "Enter number of students on lection: ";
    cin >> top.students;

    top.id = storage_->insertTopic(top);
    cout << "\n Topic created, id = " << top.id << endl;

    cout << "\n\nEnter any value to back to previous menu\n";
    char c;
    cin >> c;
    topicsMainMenu();
}