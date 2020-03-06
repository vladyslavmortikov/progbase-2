#pragma once

#include <cstdlib>
#include <cstdio>

class List
{
    void **items_;
    int size_;
    int capacity_;

  public:
    List();
    ~List();
    int size();
    void insert(int index, void *value);
    void removeAt(int index);
    void add(void *value);
    void remove(void *value);
    bool isEmpty();
    void print();
    void modifyList();
    void * & operator [](int index);  // TItem - item type

};
