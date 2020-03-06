#pragma once

#include <stdlib.h>
#include <stdio.h> 
#include <string.h>
#include <stdbool.h>
#include <math.h> 

typedef struct StrStrMap StrStrMap;

struct StrStrMap {
    void** keys;
    void** values;
    size_t size;
    size_t capacity;
};


char* String_allocFromInt(int value);
char* String_allocCopy(char* str);
char* String_allocFromDouble(double value);
StrStrMap* StrStrMap_alloc();
void Map_free (StrStrMap* self);
void StrStrMap_add(StrStrMap* self, void* key, void* value);
bool StrStrMap_contains (StrStrMap * self, void* key);
void StrStrMap_clear (StrStrMap * self);
void* StrStrMap_get(StrStrMap * self, void* key);
void * Map_remove(StrStrMap * self, char * key);
void StrStrMap_print(StrStrMap * self);

