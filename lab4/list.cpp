#include "list.hpp"

void List::print()
{
    printf("Size of list: %i\n", size());
    for (int i = 0; i < size(); i++)
    {
        printf("[%.2f] ", *((float *)this->items_[i]));
    }
    puts("");
}

List::List()
{
    this->capacity_ = 30;
    this->size_ = 0;
    this->items_ = static_cast<void **>(malloc(sizeof(void *) * this->capacity_));
}

List::~List()
{
    delete this->items_;
}

void *&List::operator[](int index)
{
    if (index < 0 || index > this->size())
    {
        abort();
    }
    return this->items_[index];
}

int List::size()
{
    return this->size_;
}

void List::insert(int index, void *value)
{
    if (index > this->size_ || index < 0)
    {
        fprintf(stderr, "ERROR: item cannot be inserted\n");
        abort();
    }
    else if (index == this->size_)
    {
        add(value);
    }
    else if (index < this->size_)
    {
        if (this->size_ + 1 < this->capacity_)
        {
            int newcap = this->capacity_ + 1;
            void *newitems_ = realloc(this->items_, sizeof(void *) * newcap);
            if (newitems_ == NULL)
            {
                free(this->items_);
                fprintf(stderr, "Reallocating memory error\n");
                abort();
            }
            this->items_ = static_cast<void **>(newitems_);
            this->capacity_ = newcap;
        }
        for (int i = this->size_; i >= index; i--)
        {
            this->items_[i + 1] = this->items_[i - 1];
        }
        this->items_[index] = value;
        this->size_++;
    }
}

void List::removeAt(int index)
{
    if (index >= this->size_ || index < 0)
    {
        printf("ERROR: Index is bigger than list's size\n");
        return;
    }
    free(this->items_[index]);
    for (int i = index; i < this->size_ - 1; i++)
    {
        this->items_[i] = this->items_[i + 1];
    }
    this->size_--;
}

void List::add(void *value)
{
    this->items_[this->size_] = value;
    this->size_ += 1;
    if (this->size_ == this->capacity_)
    {
        int newcap = this->capacity_ * 2;
        void *newitems_ = realloc(this->items_, sizeof(void *) * newcap);
        if (newitems_ == NULL)
        {
            free(this->items_);
            fprintf(stderr, "Reallocating memory error\n");
            abort();
        }
        this->items_ = static_cast<void **>(newitems_);
        ;
        this->capacity_ = newcap;
    }
}

void List::remove(void *value)
{
    for (int i = 0; i < this->size_; i++)
    {
        if (this->items_[i] == value)
        {
            free(this->items_[i]);
            for (int j = i; j < this->size_; j++)
            {
                if (j != this->size_ - 1)
                {
                    this->items_[j] = this->items_[j + 1];
                }
            }
            this->size_--;
            return;
        }
    }
    printf("ERROR: value that you want to remove isn't in list\n");
}

bool List::isEmpty()
{
    return this->size_ == 0;
}

void List::modifyList()
{
    int tmp = 0;
    for (int i = 0; i < size(); i++)
    {
        if (*((float *)this->items_[i]) > -1 && *((float *)this->items_[i]) < 1)
        {
            float *buf = static_cast<float *>(this->items_[tmp]);
            this->items_[tmp] = this->items_[i];
            this->items_[i] = buf;
            tmp++;
        }
    }
}
