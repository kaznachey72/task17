#ifndef STACK_H
#define STACK_H

#include <iostream>
#include <cstring>
#include <string>

#include "cstack.h"


//--- helpers ----------------

template <typename T> 
value_t to_value(const T &item);

template <> 
value_t to_value(const std::string &item) 
{
    value_t value;
    value.len = item.size() + 1;
    value.data = (char *) malloc(value.len * sizeof(char));
    strncpy(value.data, item.c_str(), value.len);
    return value;
}


template <typename T> 
T from_value(const value_t &value);

template <> 
std::string from_value(const value_t &value) 
{
    return std::string(value.data, value.len);
}


//--- cstack_t wrapper -------

template <typename T> 
class Stack 
{
public:
    Stack(size_t capacity)
    {
        cstack_ = cstack_new();
        cstack_ctor(cstack_, capacity);
    }

    ~Stack() 
    {
        cstack_dtor(cstack_, free_value);
        cstack_del(cstack_);
    }

    size_t size() const 
    { 
        return cstack_size(cstack_); 
    }

    void push(const T &item) 
    {
        value_t value = to_value<T>(item);
        if (!cstack_push(cstack_, value)) {
            throw "stack is full!";
        }
    }

    const T pop() 
    {
        value_t value;
        if (!cstack_pop(cstack_, &value)) {
            throw "stack is empty!";
        }
    
        T item = from_value<T>(value);
        free_value(&value);
        return item;
    }

    void clear() 
    { 
        cstack_clear(cstack_, free_value); 
    }

private:
    cstack_t *cstack_;

};

#endif  // STACK_H
