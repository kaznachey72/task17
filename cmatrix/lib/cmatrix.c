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
    cmatrix_asign(clone, matrix->data);
    return clone;
}

void cmatrix_del(cmatrix_t *matrix)
{
    if (matrix) {
        free(matrix->data);
        free(matrix);
    }
}

void cmatrix_asign(cmatrix_t *matrix, const double *data)
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
