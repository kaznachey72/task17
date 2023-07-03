#ifndef CMATRIX_H
#define CMATRIX_H

#include <stddef.h>

#ifdef __cplusplus
extern "C" {
#endif


typedef struct cmatrix_type cmatrix_t;

cmatrix_t *cmatrix_new(size_t rows, size_t cols);
cmatrix_t *cmatrix_clone(const cmatrix_t *matrix);
void cmatrix_del(cmatrix_t *matrix);

void cmatrix_assign(cmatrix_t *matrix, const double *data);
void cmatrix_set(cmatrix_t *matrix, size_t row, size_t col, double value);
double cmatrix_get(const cmatrix_t *matrix, size_t row, size_t col);

cmatrix_t *cmatrix_add(const cmatrix_t *lhs, const cmatrix_t *rhs);
cmatrix_t *cmatrix_sub(const cmatrix_t *lhs, const cmatrix_t *rhs);
cmatrix_t *cmatrix_mul(const cmatrix_t *lhs, const cmatrix_t *rhs);

bool cmatrix_is_equals(const cmatrix_t *lhs, const cmatrix_t *rhs);
void cmatrix_print(const cmatrix_t *matrix);


#ifdef __cplusplus
}
#endif


#endif  // CMATRIX_H
