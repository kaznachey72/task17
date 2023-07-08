#ifndef MATRIX_H
#define MATRIX_H

#include "cmatrix.h"


//--- cmatrix_t wrapper ------

class Matrix
{
public:
    Matrix();
    Matrix(size_t rows, size_t cols, const double *data = nullptr);
    Matrix(const Matrix &other);
    Matrix(Matrix &&other);
    ~Matrix();

    void set(size_t row, size_t col, double value);
    double get(size_t row, size_t col) const;

    Matrix operator+(const Matrix &other) const;
    Matrix operator-(const Matrix &other) const;
    Matrix operator*(const Matrix &other) const;
    bool operator==(const Matrix &other) const;

    double det() const;

    Matrix &operator=(const Matrix &other);
    Matrix &operator=(Matrix &&other);

    void print() const;

private:
    static Matrix from_cmatrix(cmatrix_t *cmatrix);

private:
    cmatrix_t *cmatrix_;

};

//--- helpers ----------------

bool is_equals(const Matrix &lhs, const Matrix &rhs); 
Matrix add(const Matrix &lhs, const Matrix &rhs);
Matrix sub(const Matrix &lhs, const Matrix &rhs); 
Matrix mul(const Matrix &lhs, const Matrix &rhs);


#endif  // MATRIX_H
