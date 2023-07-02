#include <assert.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

#include "cstack.h"

value_t to_value(int int_value) 
{
    value_t value;
    int *p = (int *) malloc(sizeof(int));
    *p = int_value;
    value.data = (char *)p;
    value.len = sizeof(int_value);
    return value;
}

int from_value(value_t *value) 
{ 
    return *((int *)value->data); 
}

void deleter(value_t *value) 
{
    if (value && value->data) {
        free(value->data);
    }
    value->data = NULL;
}

void test_cstack_ctor(cstack_t *cstack, size_t capacity)
{
    cstack_ctor(cstack, capacity);
    printf("[ Ok ] cstack_ctor( capacity = %lu )\n", capacity);

    assert(cstack_size(cstack) == 0);
    printf("[ Ok ] size: %lu\n", cstack_size(cstack));
}

void test_cstack_push(cstack_t *cstack, int int_value)
{
    bool is_pushed = cstack_push(cstack, to_value(int_value));
    assert(is_pushed);
    
    printf("       push int: %d\n", int_value);
}

void test_cstack_pop(cstack_t *cstack, int int_value)
{
    value_t value;
    bool is_popped = cstack_pop(cstack, &value);
    assert(is_popped);

    assert(from_value(&value) == int_value);
    printf("       pop int:  %d\n", from_value(&value));
    deleter(&value);
}

void test_cstack_clear(cstack_t *cstack)
{
    cstack_clear(cstack, deleter);
    printf("[ Ok ] cstack_clear\n");

    assert(cstack_size(cstack) == 0);
    printf("[ Ok ] size: %lu\n", cstack_size(cstack));
}


int main() 
{
    int int_values[] = {10, 20, 30, 40, 50};

    //--- test ctor ----------

    cstack_t *cstack = cstack_new();
    test_cstack_ctor(cstack, 100);

    //--- test push ----------

    size_t size = sizeof(int_values) / sizeof(int);
    for (size_t i = 0; i < size; ++i) {
        test_cstack_push(cstack, int_values[i]);
    }

    assert(cstack_size(cstack) == size);
    printf("[ Ok ] size: %lu\n", cstack_size(cstack));

    //---test pop ------------

    for (size_t i = size; i; --i) {
        test_cstack_pop(cstack, int_values[i - 1]);
    }

    assert(cstack_size(cstack) == 0);
    printf("[ Ok ] size: %lu\n", cstack_size(cstack));

    //---test clear ----------

    size = sizeof(int_values) / sizeof(int);
    for (size_t i = 0; i < size; ++i) {
        test_cstack_push(cstack, int_values[i]);
    }
    test_cstack_clear(cstack);

    //--- test dtor ----------

    cstack_dtor(cstack, deleter);
    cstack_del(cstack);
    
    printf("[ Ok ] ALL TESTS COMPLETED\n");

    return 0;
}
