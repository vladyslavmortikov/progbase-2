#pragma once

#include <stdlib.h>
#include <stdio.h> 
#include <string.h>
#include <stdbool.h>

#include "strstrmap.h"

typedef struct BSTree BSTree;
typedef struct BinTree BinTree;

struct BSTree {
    BinTree * root;  
    size_t size;   
};

BSTree* BSTree_alloc();
void BSTree_free(BSTree* self);
void BSTree_insert (BSTree * self, StrStrMap* value);
void BSTree_print(BSTree * self);
void BSTree_delete (BSTree * self, int key);
int BSTree_size(BSTree* self); 


