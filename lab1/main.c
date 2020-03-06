#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#include "list.h"
#include "deque.h"
//------------------------------------------------
void modifyList(List *list);
void modifyDeque(Deque *firstDeque, Deque *secondDeque, List *mainlist);
void createListFromDequeu(Deque *firstDeque, Deque *secondDeque, List *dequeList);
//------------------------------------------------
int main()
{

    FILE *myfile = fopen("data.txt", "r");

    if (myfile == NULL)
    {
        return 1;
    }

    List mainList;

    List_init(&mainList);

    float buf;

    while (fscanf(myfile, "%f", &buf) == 1)
    {
        // printf("%f\n", buf);
        float *p = malloc(sizeof(float));
        *p = buf;
        List_add(&mainList, p);
    }

    fclose(myfile);

    List_print(&mainList);
    modifyList(&mainList);
    List_print(&mainList);

    puts("-----------------------------------");

    Deque firstDeque;
    Deque secondDeque;
    List dequeList;

  
    List_init(&dequeList);
    Deque_init(&firstDeque);
    Deque_init(&secondDeque);

    modifyDeque(&firstDeque, &secondDeque, &mainList);

    createListFromDequeu(&firstDeque, &secondDeque, &dequeList);

    Deque_deinit(&firstDeque);
    Deque_deinit(&secondDeque);
    List_deinit(&mainList);

    return 0;
}

void modifyList(List *list)
{
    int tmp = 0;
    for (int i = 0; i < List_size(list); i++)
    {
        if (*((float *)list->items[i]) > -1 && *((float *)list->items[i]) < 1)
        {
            float *buf = list->items[tmp];
            list->items[tmp] = list->items[i];
            list->items[i] = buf;
            tmp++;
        }
    }
}

void fullDeque(Deque *Deque, int dSize)
{

    // float e = rand()% (10 - 1 + 1 + 1);
    for (int i = 0; i < dSize; i++)
    {
        float p = (float)i;
        // scanf("%f", &p);
        Deque_pushBack(Deque, p);
    }
    Deque_print(Deque);
}

void modifyDeque(Deque *firstDeque, Deque *secondDeque, List *mainlist)
{
    for (int i = 0; i < List_size(mainlist); i++)
    {
        float buf = *(float *)List_get(mainlist, i);
        if (i % 2 == 0)
        {
            Deque_pushFront(firstDeque, buf);
        }
        else
        {
            Deque_pushBack(secondDeque, buf);
        }
    }
    Deque_print(firstDeque);
    Deque_print(secondDeque);

}

void createListFromDequeu(Deque *firstDeque, Deque *secondDeque, List *dequeList)
{
    while (!Deque_isEmpty(firstDeque))
    {
        float *buf = malloc(sizeof(float));
        // float p = Deque_popBack(firstDeque);
        *buf = Deque_popBack(firstDeque);
        List_add(dequeList, buf);
    }
    while (!Deque_isEmpty(secondDeque))
    {
        float *buf = malloc(sizeof(float));
        *buf = Deque_popFront(secondDeque);
        List_add(dequeList, buf);
    }
    List_print(dequeList);
}
