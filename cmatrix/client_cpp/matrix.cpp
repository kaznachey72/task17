#include <iostream>
#include <utility>

#include "matrix.h"


//--- cmatrix_t wrapper ------

Matrix::Matrix()
    : Matrix(0, 0)
{
}

Matrix::Matrix(size_t rows, size_t cols, const double *data)
{
    cmatrix_ = cmatrix_new(rows, cols);
    if (data) {
        cmatrix_assign(cmatrix_, data);
    }
}

Matrix::Matrix(const Matrix &other)
{
    cmatrix_ = cmatrix_clone(other.cmatrix_);
}

Matrix::Matrix(Matrix &&other) noexcept
{
    std::swap(cmatrix_, other.cmatrix_);
}

Matrix::~Matrix()
{
    cmatrix_del(cmatrix_);
}

void Matrix::set(size_t row, size_t col, double value)
{
    cmatrix_set(cmatrix_, row, col, value);
}

double Matrix::get(size_t row, size_t col) const
{
    return cmatrix_get(cmatrix_, row, col);
}


Matrix Matrix::operator+(const Matrix &other) const
{
    cmatrix_t *calc = cmatrix_add(cmatrix_, other.cmatrix_);
    if (!calc) {
        throw "invalid operation";
    }
    return from_cmatrix(calc);
}

Matrix Matrix::operator-(const Matrix &other) const
{
    cmatrix_t *calc = cmatrix_sub(cmatrix_, other.cmatrix_);
    if (!calc) {
        throw "invalid operation";
    }   
    return from_cmatrix(calc);
}

Matrix Matrix::operator*(const Matrix &other) const
{
    cmatrix_t *calc = cmatrix_mul(cmatrix_, other.cmatrix_);
    if (!calc) {
        throw "invalid operation";
    }   
    return from_cmatrix(calc);
}

bool Matrix::operator==(const Matrix &other) const
{
    return cmatrix_is_equals(cmatrix_, other.cmatrix_);
}

double Matrix::det() const
{
    return cmatrix_det(cmatrix_);
}


Matrix &Matrix::operator=(const Matrix &other)
{
    if (this != &other) {
        Matrix tmp{other};
        std::swap(cmatrix_, tmp.cmatrix_);
    }
    return *this;
}

Matrix &Matrix::operator=(Matrix &&other) noexcept
{
    if (this != &other) {
        std::swap(cmatrix_, other.cmatrix_);
    }
    return *this;
}


void Matrix::print() const
{
    cmatrix_print(cmatrix_);
}

Matrix Matrix::from_cmatrix(cmatrix_t *cmatrix)
{
    Matrix matrix;
    std::swap(matrix.cmatrix_, cmatrix);
    cmatrix_del(cmatrix);

    return matrix;
}

//--- helpers ----------------

bool is_equals(const Matrix &lhs, const Matrix &rhs)
{
    return lhs == rhs;
}

Matrix add(const Matrix &lhs, const Matrix &rhs)
{
    return lhs + rhs;
}

Matrix sub(const Matrix &lhs, const Matrix &rhs)
{
    return lhs - rhs;
}

Matrix mul(const Matrix &lhs, const Matrix &rhs)
{
    return lhs * rhs;
}

