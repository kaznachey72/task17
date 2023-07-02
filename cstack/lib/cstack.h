#ifndef CSTACK_H
#define CSTACK_H

#ifdef __cplusplus
extern "C" {
#endif

//--- value API --------------

typedef struct {
    char *data;
    size_t len;
} value_t;


value_t make_value(char *data, size_t len);
value_t copy_value(char *data, size_t len);
void free_value(value_t *value);

//--- stack API --------------

typedef void (*deleter_t)(value_t *value);

typedef struct cstack_type cstack_t;

cstack_t *cstack_new();
void cstack_del(cstack_t *cstack);

void cstack_ctor(cstack_t *cstack, size_t capacity);
void cstack_dtor(cstack_t *cstack, deleter_t deleter);

bool cstack_push(cstack_t *cstack, value_t value);
bool cstack_pop(cstack_t *cstack, value_t *value);

size_t cstack_size(const cstack_t *cstack);
void cstack_clear(cstack_t *cstack, deleter_t);

#ifdef __cplusplus
}
#endif

#endif  // CSTACK_H
