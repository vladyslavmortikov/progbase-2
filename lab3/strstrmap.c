#include "strstrmap.h"

char* String_allocFromInt(int value) {
    char* num = malloc(sizeof(char) * 30);
    if(num == NULL) {fprintf(stderr, "String_allocFromInt: Memory allocate NULL"); abort();}
    sprintf(num, "%d", value);
    return num;
}

char* String_allocCopy(char* str) {
    int strLen = strlen(str);
    char* copy =  malloc(sizeof(char) * (strLen + 1));
    if(copy == NULL) {fprintf(stderr, "String_allocCopy: Memory allocate NULL"); abort();}
    strcpy(copy, str);
    return copy;
}

char* String_allocFromDouble(double value) {
    char* doubleNum = malloc(sizeof(char) * 100);
    if(doubleNum == NULL) {fprintf(stderr, "String_allocFromDouble: Memory allocate NULL"); abort();}
    sprintf(doubleNum, "%f", value);
    return doubleNum;
}

StrStrMap* StrStrMap_alloc() {
    StrStrMap* self = (StrStrMap*)malloc(sizeof(struct StrStrMap));
    if(self == NULL) {fprintf(stderr, "StrStrMap_alloc: malloc NULL"); abort();}
    self->capacity  = 4;
    self->keys = (void**)malloc(sizeof(void*) * self->capacity);
    if(self->keys == NULL) {fprintf(stderr, "StrStrMap_alloc: malloc keys NULL"); abort();}
    self->values = (void**)malloc(sizeof(void*) * self->capacity);
    if(self->values == NULL) {fprintf(stderr, "StrStrMap_alloc: malloc values NULL"); abort();}
    self->size = 0;
    return self;
}

void Map_free (StrStrMap* self) {
    free(self->keys);
    free(self->values);
    free(self);
}

void StrStrMap_add(StrStrMap* self, void* key, void* value) {
    char* keyStr = (char*)key;
    char* valStr = (char*)value;

    if(self->size == self->capacity) {
        int newCapacity = 4 * self->capacity;
        void** newKeys = (void**)realloc(self->keys,  sizeof(void*) * newCapacity);
        if(newKeys == NULL) {fprintf(stderr, "StrStrMap_add: malloc keys NULL"); abort();}
        void** newValues = (void**)realloc(self->values,  sizeof(void*) * newCapacity);
        if(newValues == NULL) {fprintf(stderr, "StrStrMap_add: malloc values NULL"); abort();}
        self->capacity = newCapacity;
        self->keys = newKeys;
        self->values = newValues;
    }
    self->keys[self->size] = keyStr;
    self->values[self->size] = valStr;
    self->size++;
}

bool StrStrMap_contains (StrStrMap * self, void* key) {
    for(int i = 0; i < self->size; ++i) {
        if(strcmp(self->keys[i], (char*)key) == 0) {
            return true;
        }
    }
    return false;
}

void* StrStrMap_get(StrStrMap * self, void* key) {
    if(self == NULL) return NULL;

    for(int i = 0; i < self->size; ++i) {
        if(strcmp(self->keys[i], (char*)key) == 0) {
            return self->values[i];
        }
    }
    return NULL;
}

void StrStrMap_clear (StrStrMap * self) {
    for(int i = 0; i < self->size; ++i) {
        //free(self->keys[i]);
        free(self->values[i]);
    }
}

void* Map_remove(StrStrMap * self, char * key) {
    bool contain = StrStrMap_contains(self, key);
    if(contain == false) return NULL;
    for(int i = 0; i < self->size; ++i) {
        if(strcmp(self->keys[i], (char*)key) == 0) {
            void* removeVal = self->values[i];
            for(int j = i; j < self->size - 1; ++j) {
                self->keys[j] =  self->keys[j+1];
                self->values[j] = self->values[j+1];
            }
            self->size--;
            return removeVal;
        }
    }
    return NULL;
}

void StrStrMap_print(StrStrMap * self) {
    for(int i = 0; i < self->size; ++i) {
        printf(" |%s| ", (char*)self->values[i]);
    }
    puts("");
}
