#include "deque.hpp"

Deque::Deque()
{
    this->capacity_ = 20;
    this->first_ = 10;
    this->last_ = 10;
    this->items_ = static_cast<float *>(malloc(sizeof(float) * this->capacity_));
   
}

Deque::~Deque()
{
    delete this->items_;
}
void Deque::pushFront(float value)
{
    if (this->first_ == -1)
    {
        this->first_ = 0;
        this->last_ = 0;
    }
    else if (this->first_ == 0 || this->last_ == this->capacity_ - 1)
    {
        if (this->last_ + 1 < this->capacity_)
        {
            int newCap = this->capacity_ + 1;
            void *newItems = realloc(this->items_, sizeof(float) * newCap);
            if (newItems == NULL)
            {
                free(this->items_);
                fprintf(stderr, "Reallocating memory error\n");
                abort();
            }
            this->items_ = static_cast<float *>(newItems);
            this->capacity_ = newCap;
        }
        for (int i = this->last_; i >= this->capacity_; i--)
        {
            this->items_[i + 1] = this->items_[i - 1];
        }
        this->items_[this->last_] = value;
        this->last_++;
    }
    else
    {
        this->first_--;
    }
    this->items_[this->first_] = value;
}

void Deque::pushBack(float value)
{
    this->items_[this->last_] = value;
    this->last_ += 1;
    if (this->last_ == this->capacity_)
    {
        this->last_ = 0;
    }
    if (this->last_ == this->first_)
    {
        fprintf(stderr, "Deque is full");
        int newCap = this->capacity_ * 2;
        float *newItems = static_cast<float *>(realloc(this->items_, sizeof(float) * newCap));
        if (newItems == NULL)
        {
            free(this->items_);
            fprintf(stderr, "Reallocating memory error\n");
            abort();
        }
        this->items_ = newItems;
        this->capacity_ = newCap;
    }
}

float Deque::popFront()
{
    float value = this->items_[this->first_];
    this->items_[this->first_] = -1;
    if (this->first_ == this->last_)
    {
        this->first_ = -1;
        this->last_ = -1;
    }
    else if (this->first_ == this->capacity_ - 1)
    {
        this->first_ = 0;
    }
    else
    {
        this->first_++;
    }
    return value;
}

float Deque::popBack()
{
    float value = this->items_[this->last_ - 1];
    this->items_[this->last_] = -1;
    if (this->first_ == this->last_)
    {
        this->first_ = -1;
        this->last_ = -1;
    }
    else if (this->last_ == 0)
    {
        this->last_ = this->capacity_ - 1;
    }
    else
    {
        this->last_--;
    }
    return value;
}

int Deque::size()
{
    if (this->last_ >= this->first_)
        return this->last_ - this->first_;
    return this->capacity_ - this->first_ + this->last_;
}

bool Deque::isEmpty()
{
    if (this->first_ == this->last_)
    {
        return true;
    }
    return false;
}

void Deque::print()
{
    printf("Size of deque: %i\n", size());
    for (int i = this->first_; i < this->last_; i++)
    {
        printf("[%.2f] ", this->items_[i]);
    }
    puts("");
}