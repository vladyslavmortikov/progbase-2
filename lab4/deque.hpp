#pragma once

#include <cstdlib>
#include <cstdio>

class Deque
{
    float *items_;
    int capacity_;
    int first_;
    int last_;

  public:
    Deque();
    ~Deque();
    void pushBack(float value);
    float popBack();
    void pushFront(float value);
    float popFront();

    int size();
    bool isEmpty();

    void print();
};