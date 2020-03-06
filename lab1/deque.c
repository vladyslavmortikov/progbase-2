#include "deque.h"

void Deque_init(Deque *self)
{
    self->capacity = 20;
    self->first = 10;
    self->last = 10;
    self->items = malloc(sizeof(float) * self->capacity);
}

void Deque_deinit(Deque *self)
{
    free(self->items);
}

void Deque_free(Deque *self)
{
    free(self);
    free(self->items);
}

void Deque_pushFront(Deque *self, float value)
{
    if (self->first == -1)
    {
        self->first = 0;
        self->last = 0;
    }
    else if (self->first == 0 || self->last == self->capacity - 1)
    {
        if (self->last + 1 < self->capacity)
        {
            int newCap = self->capacity + 1;
            void *newItems = realloc(self->items, sizeof(float) * newCap);
            if (newItems == NULL)
            {
                free(self->items);
                fprintf(stderr, "Reallocating memory error\n");
                abort();
            }
            self->items = newItems;
            self->capacity = newCap;
        }
        for (size_t i = self->last; i >= self->capacity; i--)
        {
            self->items[i + 1] = self->items[i - 1];
        }
        self->items[self->last] = value;
        self->last++;
    }
    else
    {
        self->first--;
    }
    self->items[self->first] = value;
}

void Deque_pushBack(Deque *self, float value)
{
    self->items[self->last] = value;
    self->last += 1;
    if (self->last == self->capacity)
    {
        self->last = 0;
    }
    if (self->last == self->first)
    {
        fprintf(stderr, "Deque is full");
        int newCap = self->capacity * 2;
        float *newItems = realloc(self->items, sizeof(float) * newCap);
        if (newItems == NULL)
        {
            free(self->items);
            fprintf(stderr, "Reallocating memory error\n");
            abort();
        }
        self->items = newItems;
        self->capacity = newCap;
    }
}

float Deque_popFront(Deque *self)
{
    float value = self->items[self->first];
    self->items[self->first] = -1;
    if (self->first == self->last)
    {
        self->first = -1;
        self->last = -1;
    }
    else if (self->first == self->capacity - 1)
    {
        self->first = 0;
    }
    else
    {
        self->first++;
    }
    return value;
}

float Deque_popBack(Deque *self)
{
    float value = self->items[self->last - 1];
    self->items[self->last] = -1;
    if (self->first == self->last)
    {
        self->first = -1;
        self->last = -1;
    }
    else if (self->last == 0)
    {
        self->last = self->capacity - 1;
    }
    else
    {
        self->last--;
    }
    return value;
}

size_t Deque_size(Deque *self)
{
    if (self->last >= self->first)
        return self->last - self->first;
    return self->capacity - self->first + self->last;
}

bool Deque_isEmpty(Deque *self)
{
    if (self->first == self->last)
    {
        return true;
    }
    return false;
}

void Deque_print(Deque *self)
{
    printf("Size of deque: %zu\n", Deque_size(self));
    for (int i = self->first; i < self->last; i++)
    {
        printf("[%.2f] ", self->items[i]);
    }
    puts("");
}