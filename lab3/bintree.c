#include "bintree.h"

struct BinTree 
{
   StrStrMap* value;      // set on init/alloc
   BinTree* left;  // set to NULL on init
   BinTree* right; // set to NULL on init
};

static void BinTree_free (BinTree * self);
static BinTree* lookupPlaceForKey(BinTree * self, StrStrMap* value);
static BinTree* BinTree_alloc();
static void BinTree_init (BinTree* self, StrStrMap* value);
static BinTree* BinTree_delete(BinTree* self, int key);
static int BinTree_size(BinTree* self);
static void printNode(BinTree * node, char pos, int lvl);
static void printValueOnLevel(BinTree * node, char pos, int lvl);

static BinTree* BinTree_alloc () {
    BinTree* self = (BinTree*)malloc(sizeof(struct BinTree));
    if(self == NULL) {fprintf(stderr, "BinTree_allo: BinTree* root malloc NULL"); abort();}
    self->value = NULL;
    self->right = NULL;
    self->left = NULL;

    return self;
}

static void BinTree_init (BinTree* self, StrStrMap* value) {
    self->value = value;
}

BSTree* BSTree_alloc() {
    BSTree* self = (BSTree*)malloc(sizeof(struct BSTree));
    if(self == NULL) {fprintf(stderr, "BSTree_alloc: BSTree* self malloc NULL"); abort();}

    BinTree* root = NULL;

    self->root = root;
    self->size = 0;

    return self;
} 

static void BinTree_free (BinTree * self) {
    if(self == NULL) return;

    BinTree_free(self->right);
    BinTree_free(self->left);

    free(self);
}

void BSTree_free(BSTree* self) {
    if(self->root != NULL) BinTree_free(self->root);
    free(self);
}

static BinTree* lookupPlaceForKey(BinTree* self, StrStrMap* map) {
    if(self == NULL) {self = BinTree_alloc(); BinTree_init(self, map); return self;}

    char* mapId = StrStrMap_get(map, "id");
    int value = atoi(mapId);

    char* idValue = StrStrMap_get(self->value, "id");
    int id = atoi(idValue);

    if(value > id) { self->right = lookupPlaceForKey(self->right, map);}
    else if(value <= id) { self->left = lookupPlaceForKey(self->left, map);}

    return self;
}

void BSTree_insert (BSTree * self, StrStrMap* value) {
    if(self->root == NULL) {
        self->root = lookupPlaceForKey(self->root, value);
    } else {
        lookupPlaceForKey(self->root, value);
    }
    self->size++;
}

static void BinTree_print(BinTree* self) {
    printNode(self, '+', 0);
}

static void printNode(BinTree * node, char pos, int lvl) {  
   bool hasChild = node != NULL && (node->left != NULL || node->right != NULL);
   if (hasChild) printNode(node->right, 'R', lvl + 1);
   printValueOnLevel(node, pos, lvl);
   if (hasChild) printNode(node->left,  'L', lvl + 1);
}


void BSTree_print(BSTree * self) {
    BinTree_print(self->root);
}

static BinTree* BinTree_delete(BinTree* self, int key) {
    if(self == NULL) return self;

    char* selfKeyStr = StrStrMap_get(self->value, "Test Time");
    int selfKey = atoi(selfKeyStr);

    self->right = BinTree_delete(self->right, key);
    self->left = BinTree_delete(self->left, key);

    if(selfKey > key) {
        if(self->left == NULL) {
            BinTree* temp = self->right;
            free(self);
            return temp;
        } else if(self->right == NULL) {
            BinTree* temp = self->left;
            free(self);
            return temp;
        } else {
            BinTree* rChild = self->right;

            BinTree* iter = self->right;
            while(iter->left != NULL) {
                rChild = iter;
                iter = iter->left;
            }

            rChild->left = iter->right;
            self->value = iter->value;
            
            free(iter);
        }
    }

    return self;
}

void BSTree_delete (BSTree * self, int key) {
    self->root = BinTree_delete(self->root, key);
    self->size = BinTree_size(self->root);
}

static int BinTree_size(BinTree* self) {
    if(self == NULL) return 0;

    return BinTree_size(self->right) + BinTree_size(self->left) + 1;
}

int BSTree_size(BSTree* self) {
    return self->size;
}

static void printValueOnLevel(BinTree * node, char pos, int lvl) {
   for (int i = 0; i < lvl; i++) {
       printf("....");
   }
   printf("%c: ", pos);

   if (node == NULL) {
       printf("(null)\n");
   } else {
       StrStrMap_print(node->value);
       printf("\n \n");
   }
}

