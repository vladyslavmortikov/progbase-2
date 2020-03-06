#include "list.h"

List *List_alloc(void)
{
    List *list = malloc(sizeof(List));
    List_init(list);
    return list;
}

void List_free(List * self)
{
    List_deinit(self);
    free(self);
}

void List_print(List * self)
{ 
    printf("Size of list: %zu\n", List_size(self) );
    for(int i = 0; i < List_size(self); i++){
        printf("[%.2f] ", *((float*)self->items[i]));
    }
    puts("");
}

void List_init(List * self)
{
    self->capacity = 30;
    self->size = 0;
    self->items = malloc(sizeof(void *) * self->capacity);
}

void List_deinit(List * self)
{
    free(self->items);
}

void *List_get(List * self, int index)
{
    return self->items[index];
}

void List_set(List * self, int index, void * value)
{
}

size_t List_size(List * self)
{
    return self->size;
}

void List_insert(List * self, int index, void * value)
{
     if (index > self->size || index < 0)
    {
        fprintf(stderr, "ERROR: item cannot be inserted\n");
        abort();
    }
    else if (index == self->size)
    {
        List_add(self, value);
    }
    else if (index < self->size)
    {
        if (self->size + 1 < self->capacity)
        {
            int newcap = self->capacity + 1;
            void *newitems = realloc(self->items, sizeof(void *) * newcap);
            if (newitems == NULL)
            {
                free(self->items);
                fprintf(stderr, "Reallocating memory error\n");
                abort();
            }
            self->items = newitems;
            self->capacity = newcap;
        }
        for (size_t i = self->size; i >= index; i--)
        {
            self->items[i + 1] = self->items[i - 1];
        }
        self->items[index] = value;
        self->size++;
    }
}

void List_removeAt(List * self, int index)
{
   if (index >= self->size || index < 0)
    {
        printf("ERROR: Index is bigger than list's size\n");
        return;
    }
    free(self->items[index]);
    for (size_t i = index; i < self->size - 1; i++)
    {
        self->items[i] = self->items[i + 1];
    }
    self->size--;
}

void List_add(List * self, void * value)
{
    self->items[self->size] = value;
    self->size += 1;
    if (self->size == self->capacity)
    {
        int newcap = self->capacity * 2;
        void *newitems = realloc(self->items, sizeof(void *) * newcap);
        if (newitems == NULL)
        {
            free(self->items);
            fprintf(stderr, "Reallocating memory error\n");
            abort();
        }
        self->items = newitems;
        self->capacity = newcap;
    }
}

void List_remove(List * self, void * value)
{
    for (size_t i = 0; i < self->size; i++)
    {
        if (self->items[i] == value)
        {
            free(self->items[i]);
            for (size_t j = i; j < self->size; j++)
            {
                if (j != self->size - 1)
                {
                    self->items[j] = self->items[j + 1];
                }
            }
            self->size--;
            return;
        }
    }
    printf("ERROR: value that you want to remove isn't in list\n");
}

int List_indexOf(List * self, void * value)
{
    return -1;
}

bool List_contains(List * self, void * value)
{
    return false;
}

bool List_isEmpty(List * self)
{
    return self->size == 0;
}

void List_clear(List * self)
{
  self->size = 0;  
}
