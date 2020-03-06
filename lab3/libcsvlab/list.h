#pragma once

#include <stdlib.h>
#include <stdio.h> 
#include <string.h>

typedef struct List List;

struct List {
    void** items;
    size_t size;
    size_t capacity;
};

void List_init(List* self);
void List_deinit(List* self);
void List_add(List* list, void* item);
List* List_alloc();
int List_size(List* self);
void* List_getIndexOf(List* self, int index);
void List_clear(List* self);
void List_free(List* self);
