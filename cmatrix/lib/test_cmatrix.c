#include <math.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

#include "cmatrix.h"


typedef enum {
    OP_ADD,
    OP_SUB,
    OP_MUL,
} operation_t;

int test(operation_t op, const cmatrix_t *lhs, const cmatrix_t *rhs, const cmatrix_t *result) 
{
    cmatrix_t *calc = NULL;
    switch (op) {
        case OP_ADD:
            calc = cmatrix_add(lhs, rhs);
            break;
        case OP_SUB:
            calc = cmatrix_sub(lhs, rhs);
            break;
        case OP_MUL:
            calc = cmatrix_mul(lhs, rhs);
            break;
    }

    bool is_equals = cmatrix_is_equals(result, calc);
    cmatrix_del(calc);

    return is_equals;
}

void test_add()
{
    size_t rows = 3;
    size_t cols = 4;
    
    double lhs_data[] = {
         1,  2,  3,  4,
         5,  6,  7,  8,
         9, 10, 11, 12,
    };
    double rhs_data[] = { 
        12, 11, 10,  9,  
         8,  7,  6,  5,  
         4,  3,  2,  1, 
    };
    double res_data[] = {
        13, 13, 13, 13,
        13, 13, 13, 13,
        13, 13, 13, 13,
    };

    cmatrix_t *lhs = cmatrix_new(rows, cols);
    cmatrix_t *rhs = cmatrix_new(rows, cols);
    cmatrix_t *res = cmatrix_new(rows, cols);

    cmatrix_assign(lhs, lhs_data);
    cmatrix_assign(rhs, rhs_data);
    cmatrix_assign(res, res_data);

    //cmatrix_print(lhs);
    //cmatrix_print(rhs);
    //cmatrix_print(res);

    bool is_ok = test(OP_ADD, lhs, rhs, res);

    cmatrix_del(lhs);
    cmatrix_del(rhs);
    cmatrix_del(res);

    printf("[ %s ] TEST: A + B\n", (is_ok ? "Ok " : "Err" ));
}

void test_sub()
{
    size_t rows = 3;
    size_t cols = 4;

    double lhs_data[] = {
        13, 13, 13, 13,
        13, 13, 13, 13,
        13, 13, 13, 13,
    };
    double rhs_data[] = {
         1,  2,  3,  4,
         5,  6,  7,  8,
         9, 10, 11, 12,
    };
    double res_data[] = {
        12, 11, 10,  9,
         8,  7,  6,  5,
         4,  3,  2,  1,
    };

    cmatrix_t *lhs = cmatrix_new(rows, cols);
    cmatrix_t *rhs = cmatrix_new(rows, cols);
    cmatrix_t *res = cmatrix_new(rows, cols);

    cmatrix_assign(lhs, lhs_data);
    cmatrix_assign(rhs, rhs_data);
    cmatrix_assign(res, res_data);

    //cmatrix_print(lhs);
    //cmatrix_print(rhs);
    //cmatrix_print(res);

    bool is_ok = test(OP_SUB, lhs, rhs, res);

    cmatrix_del(lhs);
    cmatrix_del(rhs);
    cmatrix_del(res);

    printf("[ %s ] TEST: A - B\n", (is_ok ? "Ok " : "Err" ));
}

void test_mul()
{
    size_t rows = 3;
    size_t cols = 3;

    double lhs_data[] = {
        -4,   5,  -2,
         0,  -7,  11,
         8, -10, -21,
    };
    double rhs_data[] = {
         2,  3, -5,
        -6, 13, -7,
        12, 15, -6,
    };
    double res_data[] = {
         -62,   23,  -3,
         174,   74, -17,
        -176, -421, 156,
    };

    cmatrix_t *lhs = cmatrix_new(rows, cols);
    cmatrix_t *rhs = cmatrix_new(rows, cols);
    cmatrix_t *res = cmatrix_new(rows, cols);

    cmatrix_assign(lhs, lhs_data);
    cmatrix_assign(rhs, rhs_data);
    cmatrix_assign(res, res_data);

    //cmatrix_print(lhs);
    //cmatrix_print(rhs);
    //cmatrix_print(res);

    bool is_ok = test(OP_MUL, lhs, rhs, res);

    cmatrix_del(lhs);
    cmatrix_del(rhs);
    cmatrix_del(res);

    printf("[ %s ] TEST: A * B\n", (is_ok ? "Ok " : "Err" ));
}

void test_det()
{
    size_t rows = 3;
    size_t cols = 3;
    
    double data[] = {
         -62,   23,  -3,
         174,   74, -17,
        -176, -421, 156,
    };

    double det = -646800;

    cmatrix_t *matrix = cmatrix_new(rows, cols);
    cmatrix_assign(matrix, data);
    //cmatrix_print(matrix);

    double calc_det = cmatrix_det(matrix);
    cmatrix_del(matrix);

    bool is_ok = fabs(det - calc_det) < 1e-5;
    printf("[ %s ] TEST: det(A)\n", (is_ok ? "Ok " : "Err" ));    
}


int main ()
{
    test_add();
    test_sub();
    test_mul();
    test_det();

return 0;
}
