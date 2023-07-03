#include <iostream>

#include "matrix.h"


enum class OP { ADD, SUB, MUL };

int test(OP op, const Matrix &lhs, const Matrix &rhs, const Matrix &result) 
{
    Matrix calc;
    switch (op) {
        case OP::ADD:
            calc = lhs + rhs;
            break;
        case OP::SUB:
            calc = lhs - rhs;
            break;
        case OP::MUL:
            calc = lhs * rhs;
            break;
    }

    return result == calc;
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

    Matrix lhs{rows, cols, lhs_data};
    Matrix rhs{rows, cols, rhs_data};
    Matrix res{rows, cols, res_data};

    //lhs.print();
    //rhs.print();
    //res.print();

    bool is_ok = test(OP::ADD, lhs, rhs, res);
    std::cout << "[ " << (is_ok ? "Ok " : "Err" )  << " ] TEST: A + B" << std::endl;
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

    Matrix lhs{rows, cols, lhs_data};
    Matrix rhs{rows, cols, rhs_data};
    Matrix res{rows, cols, res_data};

    //lhs.print();
    //rhs.print();
    //res.print();

    bool is_ok = test(OP::SUB, lhs, rhs, res);
    std::cout << "[ " << (is_ok ? "Ok " : "Err" )  << " ] TEST: A - B" << std::endl;
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

    Matrix lhs{rows, cols, lhs_data};
    Matrix rhs{rows, cols, rhs_data};
    Matrix res{rows, cols, res_data};

    //lhs.print();
    //rhs.print();
    //res.print();

    bool is_ok = test(OP::MUL, lhs, rhs, res);
    std::cout << "[ " << (is_ok ? "Ok " : "Err" )  << " ] TEST: A * B" << std::endl;
}

int main ()
{
    test_add();
    test_sub();
    test_mul();
    return 0;
}
