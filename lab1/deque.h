#pragma once

#include <stdlib.h>
#include <stdbool.h>
#include <stdio.h>

struct __Deque
{
    float *items;
    int capacity;
    int first;
    int last;
};
typedef struct __Deque Deque;

void Deque_init(Deque *self);
void Deque_deinit(Deque *self);
Deque *Deque_alloc(void);
void Deque_free(Deque *self);

void Deque_pushBack(Deque *self, float value);
float Deque_popBack(Deque *self);
void Deque_pushFront(Deque *self, float value);
float Deque_popFront(Deque *self);

size_t Deque_size(Deque *self);
bool Deque_isEmpty(Deque *self);

void Deque_print(Deque *self);