#pragma once

#include <stdlib.h>
#include <stdio.h> 
#include <string.h>

typedef struct Vec Vec;

Vec* Vec_init(const int length);
void Vec_deinit(Vec* self);
void Vec_add(Vec* self, char ch);
void Vec_print(Vec* self);
char* Vec_toStr(Vec* self);
