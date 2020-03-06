#include "vec.h"

struct Vec {
    char* items;
    size_t len;
    size_t capacity;
};

Vec* Vec_init(const int length) {
    if(length <= 0) {fprintf(stderr, "Memory can't be allocated ");  abort();}
    Vec* self = malloc(sizeof(struct Vec));
    if(self == NULL) {fprintf(stderr, "Memory can't be allocated ");  abort();}
    self->capacity = 4 * length;
    self->items = malloc(sizeof(char) * self->capacity);
    if(self->items == NULL) {fprintf(stderr, "Memory can't be allocated ");  abort();}
    self->len = 0;
    return self;
}

void Vec_deinit(Vec* self) {
    free(self->items);
    free(self);
}

void Vec_add(Vec* self, char ch) {
    if(self->capacity == self->len) {
        int newCapacity = 4 * self->capacity;
        char* newItems = realloc(self->items ,sizeof(char) * newCapacity); 
        if(newItems == NULL) {
            Vec_deinit(self);
            fprintf(stderr, "Memory can't be allocated ");
            abort();
        }
        self->capacity = newCapacity;
        self->items = newItems;
    }
    self->items[self->len] = ch;
    self->len++;
}

void Vec_print(Vec* self) { 
    puts(self->items);
}

char* Vec_toStr(Vec* self) {
    return self->items;
}
