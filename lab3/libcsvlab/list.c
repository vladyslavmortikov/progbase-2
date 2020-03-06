#include "list.h"

void List_init(List* self) {
    self->capacity = 4;
    self->items = malloc(sizeof(void*) * self->capacity);
    if(self->items == NULL) {fprintf(stderr, "MEMORY ERROR"), abort();}
    self->size = 0;
}

void List_deinit(List* self) {
    free(self->items);
} 

void List_add(List* list, void* item) {
    if(list->size == list->capacity) {
        int newCapacity = 4 * list->capacity;
        void* newItems = realloc(list->items, sizeof(void*) * newCapacity);
        if(newItems == NULL) {fprintf(stderr, "fillStudentsList: realloc error"); abort();}
        list->capacity = newCapacity;
        list->items = newItems;
    }
    list->items[list->size] = item;
    list->size++;
}

List* List_alloc() {
    List* self = malloc(sizeof(struct List));
    if(self == NULL) {fprintf(stderr, "MEMORY ERROR"), abort();}
    self->capacity = 4;
    self->items = malloc(sizeof(void*) * self->capacity);
    if(self->items == NULL) {fprintf(stderr, "MEMORY ERROR"), abort();}
    self->size = 0;
    return self;
}

int List_size(List* self) {
    if(self != NULL) return self->size;
    return -1;
}


void* List_getIndexOf(List* self, int index) {
    if(index < self->size) return self->items[index];
    return NULL;
}

void List_clear(List* self) {
    for(size_t j = 0; j < self->size; ++j) {
            free(self->items[j]);
    }
}

void List_free(List* self) {
    free(self->items);
    free(self); 
}
