#include <assert.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

#include "cstack.h"

//--- stack ------------------

struct cstack_type {
    size_t cur_size;
    size_t capacity;
    value_t *values;
};


cstack_t *cstack_new() 
{ 
    return (cstack_t *) malloc(sizeof(cstack_t)); 
}

void cstack_del(cstack_t *stack) 
{ 
    free(stack); 
}

void cstack_ctor(cstack_t *cstack, size_t capacity) 
{
    cstack->cur_size = 0;
    cstack->capacity = capacity;
    cstack->values = (value_t *) malloc(capacity * sizeof(value_t));
}

void cstack_dtor(cstack_t *cstack, deleter_t deleter) 
{
    cstack_clear(cstack, deleter);
    free(cstack->values);
}

bool cstack_push(cstack_t *cstack, value_t value)
{
    if (cstack->cur_size < cstack->capacity) {
        cstack->values[cstack->cur_size] = value;
        ++cstack->cur_size;
        return true;
    }
    return false;
}

bool cstack_pop(cstack_t *cstack, value_t *value)
{
    if (cstack->cur_size > 0) {
        --cstack->cur_size;
        *value = cstack->values[cstack->cur_size];
        return true;
    }
    return false;
}

size_t cstack_size(const cstack_t *cstack) 
{ 
    return cstack->cur_size; 
}

void cstack_clear(cstack_t *cstack, deleter_t deleter) 
{
    value_t value;
    size_t len = cstack_size(cstack);
    for (size_t i = 0; i < len; ++i) {
        bool is_ok = cstack_pop(cstack, &value);
        assert(is_ok);
        if (deleter) {
            deleter(&value);
        }
    }
}

//--- value ------------------

value_t make_value(char *data, size_t len)
{
    value_t value;
    value.data = data;
    value.len = len;
    return value;
}

value_t copy_value(char *data, size_t len)
{
    char *buf = (char *) malloc(len * sizeof(char));
    strncpy(buf, data, len);
    return make_value(buf, len);
}

void free_value(value_t *value)
{
    if (value && value->data) {
        free(value->data);
        value->data = NULL;
    }
}
