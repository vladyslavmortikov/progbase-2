

#include "list.hpp"
#include "deque.hpp"
//------------------------------------------------
void modifyDeque(Deque *firstDeque, Deque *secondDeque, List *mainlist);
void createListFromDeque(Deque *firstDeque, Deque *secondDeque, List *dequeList);
//------------------------------------------------
int main()
{

    FILE *myfile = fopen("data.txt", "r");

    if (myfile == NULL)
    {
        return 1;
    }


    List mainList;

    float buf;

    while (fscanf(myfile, "%f", &buf) == 1)
    {
        // printf("%f\n", buf);
        float *p = static_cast<float *>(malloc(sizeof(float)));
        *p = buf;
        mainList.add(p);
    }

    fclose(myfile);

    mainList.print();
    //------------------------------------
    mainList.modifyList();
    //------------------------------------
    mainList.print();

    puts("-----------------------------------");

    Deque firstDeque;
    Deque secondDeque;
    List dequeList;


    modifyDeque(&firstDeque, &secondDeque, &mainList);

    createListFromDeque(&firstDeque, &secondDeque, &dequeList);

    //------------------------------------

    return 0;
}

void modifyDeque(Deque *firstDeque, Deque *secondDeque, List *mainlist)
{
    for (int i = 0; i < mainlist->size(); i++)
    {
        float buf = *(float *)(*mainlist)[i];
        if (i % 2 == 0)
        {
            firstDeque->pushFront(buf);
        }
        else
        {
            secondDeque->pushBack(buf);
        }
    }
    firstDeque->print();
    secondDeque->print();

}

void createListFromDeque(Deque *firstDeque, Deque *secondDeque, List *dequeList)
{
    while (!firstDeque->isEmpty())
    {
        float *buf = static_cast<float *>(malloc(sizeof(float)));
        // float p = Deque_popBack(firstDeque);
        *buf = firstDeque->popBack();
        dequeList->add(buf);
    }
    while (!secondDeque->isEmpty())
    {
        float *buf = static_cast<float *>(malloc(sizeof(float)));
        *buf = secondDeque->popFront();
        dequeList->add(buf);
    }
    dequeList->print();
}
