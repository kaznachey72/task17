#include <float.h>
#include <math.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "cmatrix.h"


struct cmatrix_type
{
    size_t rows;
    size_t cols;
    double *data;
};

cmatrix_t *cmatrix_new(size_t rows, size_t cols)
{
    cmatrix_t *matrix = (cmatrix_t *) malloc(sizeof(cmatrix_t));
    if (!matrix) {
        fprintf(stderr, "error: bad alloc\n");
        exit(EXIT_FAILURE);
    }

    matrix->rows = rows;
    matrix->cols = cols;
    matrix->data = (double *) calloc(rows * cols, sizeof(double));
    return matrix;
}

cmatrix_t *cmatrix_clone(const cmatrix_t *matrix)
{
    cmatrix_t *clone = cmatrix_new(matrix->rows, matrix->cols);
    cmatrix_assign(clone, matrix->data);
    return clone;
}

void cmatrix_del(cmatrix_t *matrix)
{
    if (matrix) {
        free(matrix->data);
        free(matrix);
    }
}

void cmatrix_assign(cmatrix_t *matrix, const double *data)
{
    size_t size = matrix->rows * matrix->cols;
    memcpy(matrix->data, data, size * sizeof(double));
}

void cmatrix_set(cmatrix_t *matrix, size_t row, size_t col, double value)
{
    size_t index = row * matrix->cols + col;    
    matrix->data[index] = value;
}

double cmatrix_get(const cmatrix_t *matrix, size_t row, size_t col)
{
    size_t index = row * matrix->cols + col;
    return matrix->data[index];
}

cmatrix_t *cmatrix_add(const cmatrix_t *lhs, const cmatrix_t *rhs)
{
    size_t rows = lhs->rows;
    size_t cols = lhs->cols;

    if (rows != rhs->rows || cols != rhs->cols) {
        return NULL;
    }

    cmatrix_t *matrix = cmatrix_new(rows, cols);
    for (size_t row = 0; row < rows; ++row) {
        for (size_t col = 0; col < cols; ++col) {
            size_t index = row * cols + col;
            matrix->data[index] = lhs->data[index] + rhs->data[index];
        }
    }
    
    return matrix;
}

cmatrix_t *cmatrix_sub(const cmatrix_t *lhs, const cmatrix_t *rhs)
{
    size_t rows = lhs->rows;
    size_t cols = lhs->cols;

    if (rows != rhs->rows || cols != rhs->cols) {
        return NULL;
    }   

    cmatrix_t *matrix = cmatrix_new(rows, cols);
    for (size_t row = 0; row < rows; ++row) {
        for (size_t col = 0; col < cols; ++col) {
            size_t index = row * cols + col;
            matrix->data[index] = lhs->data[index] - rhs->data[index];
        }   
    }   
        
    return matrix;
}

cmatrix_t *cmatrix_mul(const cmatrix_t *lhs, const cmatrix_t *rhs)
{
    // A[m,k] x B[k, n] = C[m, n]

    if (lhs->cols != rhs->rows) {
        return NULL;
    }

    size_t rows = lhs->rows;
    size_t cols = rhs->cols;

    cmatrix_t *matrix = cmatrix_new(rows, cols);
    for (size_t row = 0; row < rows; ++row) {
        for (size_t col = 0; col < cols; ++col) {
            size_t index = row * cols + col;
            matrix->data[index] = 0;
            
            for (size_t i = 0; i < lhs->cols; ++i) {
                matrix->data[index] += lhs->data[row * lhs->cols + i] * rhs->data[i * cols + col];
            }
        }
    }
    return matrix;
}

cmatrix_t *cmatrix_gaussian_elimination(const cmatrix_t *matrix, size_t *ret_swap_count)
{
    cmatrix_t *ret_matrix = cmatrix_clone(matrix);
    size_t rows = ret_matrix->rows;
    size_t cols = ret_matrix->cols;

    size_t swap_count = 0;
    for (size_t i = 0; i < rows-1; ++i) {
        for (size_t k = i+1; k < rows; ++k) {
            if (fabs(ret_matrix->data[i * cols + i]) < fabs(ret_matrix->data[k * cols + i])) {
                ++swap_count;
                for (size_t j = 0; j < cols; ++j) {
                    double temp = ret_matrix->data[i * cols + j];
                    ret_matrix->data[i * cols + j] = ret_matrix->data[k * cols + j];
                    ret_matrix->data[k * cols + j] = temp;
                }
            }
        }
    
        for (size_t k = i+1; k < rows; ++k) {
            double ratio = ret_matrix->data[k * cols + i] / ret_matrix->data[i * cols + i];
            for (size_t j = 0; j < cols; ++j) {
                ret_matrix->data[k * cols + j] = ret_matrix->data[k * cols + j] - ratio * ret_matrix->data[i * cols + j];
            }
        }
    }

    if (ret_swap_count) {
        *ret_swap_count = swap_count;
    }

    return ret_matrix;
}

double cmatrix_det(const cmatrix_t *matrix) 
{
    if (matrix->cols != matrix->rows) {
        return 0. / 0.; // nan
    }
    
    size_t rows = matrix->rows;
    size_t cols = matrix->cols;

    size_t swap_count = 0;
    cmatrix_t * ret_matrix = cmatrix_gaussian_elimination(matrix, &swap_count);

    double det = pow(-1.0, (double)swap_count);
    for (size_t i = 0 ; i < rows; ++i) {
        det *= ret_matrix->data[i * cols + i];
    }
    cmatrix_del(ret_matrix);
    
    return det;
}


bool cmatrix_is_equals(const cmatrix_t *lhs, const cmatrix_t *rhs)
{
    size_t rows = lhs->rows;
    size_t cols = lhs->cols;
    
    if (rows != rhs->rows || cols != rhs->cols) {
        return false;
    }
    
    for (size_t row = 0; row < rows; ++row) { 
        for (size_t col = 0; col < cols; ++col) { 
            size_t index = row * cols + col;
            bool is_equals = false;
            {
                double a = lhs->data[index];
                double b = rhs->data[index];
                is_equals = (fabs(a - b) < (DBL_EPSILON * fabs(a + b)));
            }
            if (!is_equals) {
                return false;
            }
        }
    }
        
    return true;
}

void cmatrix_print(const cmatrix_t *matrix)
{
    size_t rows = matrix->rows;
    size_t cols = matrix->cols;

    for (size_t row = 0; row < rows; ++row) {
        for (size_t col = 0; col < cols; ++col) {
            size_t index = row * cols + col;
            printf("%0.2f\t", matrix->data[index]);
        }
        printf("\n");
    }
    printf("\n");
}
