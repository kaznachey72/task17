#ifndef MATRIX_H
#define MATRIX_H

typedef struct cmatrix_type cmatrix_t;

cmatrix_t *cmatrix_new(size_t rows, size_t cols);
void cmatrix_del(cmatrix_t *matrix);

void cmatrix_asign(cmatrix_t *matrix, const double *data);
void cmatrix_set(cmatrix_t *matrix, size_t row, size_t col, double value);
double cmatrix_get(const cmatrix_t *matrix, size_t row, size_t col);

cmatrix_t *cmatrix_add(const cmatrix_t *lhs, const cmatrix_t *rhs);
cmatrix_t *cmatrix_sub(const cmatrix_t *lhs, const cmatrix_t *rhs);
cmatrix_t *cmatrix_mul(const cmatrix_t *lhs, const cmatrix_t *rhs);

bool cmatrix_is_equals(const cmatrix_t *lhs, const cmatrix_t *rhs);
void cmatrix_print(const cmatrix_t *matrix);

#endif  // MATRIX_H
