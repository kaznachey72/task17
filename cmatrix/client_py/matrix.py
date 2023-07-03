#!/usr/bin/env python3

from ctypes import c_size_t, c_bool, c_double, c_void_p, cdll
import ctypes


def list_to_array(data):
    array_type = ctypes.c_double * len(data)
    return array_type(*data)


class WrapperMatrix(object):
    def __init__(self):
        self._lib = cdll.LoadLibrary("libcmatrix.so")

        # cmatrix_t *cmatrix_new(size_t rows, size_t cols);
        self.new = self._lib.cmatrix_new
        self.new.argtypes = [c_size_t, c_size_t]
        self.new.restype = c_void_p

        # cmatrix_t *cmatrix_clone(const cmatrix_t *matrix);
        self.clone = self._lib.cmatrix_clone
        self.clone.argtypes = [c_void_p]
        self.clone.restype = c_void_p

        # void cmatrix_del(cmatrix_t *matrix);
        self.delete = self._lib.cmatrix_del
        self.delete.argtypes = [c_void_p]

        # void cmatrix_assign(cmatrix_t *matrix, const double *data);
        self.assign = self._lib.cmatrix_assign
        self.assign.argtypes = [c_void_p, c_void_p]

        # void cmatrix_set(cmatrix_t *matrix, size_t row, size_t col, double value);
        self.set = self._lib.cmatrix_set
        self.set.argtypes = [c_void_p, c_size_t, c_size_t, c_double]

        # double cmatrix_get(const cmatrix_t *matrix, size_t row, size_t col);
        self.get = self._lib.cmatrix_get
        self.get.argtypes = [c_void_p, c_size_t, c_size_t]
        self.get.restype = c_double

        # cmatrix_t *cmatrix_add(const cmatrix_t *lhs, const cmatrix_t *rhs);
        self.add = self._lib.cmatrix_add
        self.add.argtypes = [c_void_p, c_void_p]
        self.add.restype = c_void_p

        # cmatrix_t *cmatrix_sub(const cmatrix_t *lhs, const cmatrix_t *rhs);
        self.sub = self._lib.cmatrix_sub
        self.sub.argtypes = [c_void_p, c_void_p]
        self.sub.restype = c_void_p

        # cmatrix_t *cmatrix_mul(const cmatrix_t *lhs, const cmatrix_t *rhs);
        self.mul = self._lib.cmatrix_mul
        self.mul.argtypes = [c_void_p, c_void_p]
        self.mul.restype = c_void_p

        # bool cmatrix_is_equals(const cmatrix_t *lhs, const cmatrix_t *rhs);
        self.is_equals = self._lib.cmatrix_is_equals
        self.is_equals.argtypes = [c_void_p, c_void_p]
        self.is_equals.restype = c_bool

        # void cmatrix_print(const cmatrix_t *matrix);
        self.pr = self._lib.cmatrix_print
        self.pr.argtypes = [c_void_p]


class Matrix(object):
    def __init__(self, rows, cols):
        self._api = WrapperMatrix()
        self._ptr = self._api.new(rows, cols)

    def __del__(self):
        self._api.delete(self._ptr)

    def assign(self, data):
        self._api.assign(self._ptr, list_to_array(data))

    def set(self, row, col, value):
        self._api.set(self._ptr, row, col, value)

    def get(self, row, col):
        return self._api.get(self._ptr, row, col)

    def add(self, other):
        matrix = Matrix(0, 0);
        matrix._ptr = self._api.add(self._ptr, other._ptr)
        return matrix

    def sub(self, other):
        matrix = Matrix(0, 0);
        matrix._ptr = self._api.sub(self._ptr, other._ptr)
        return matrix

    def mul(self, other):
        matrix = Matrix(0, 0); 
        matrix._ptr = self._api.mul(self._ptr, other._ptr)
        return matrix

    def is_equals(self, other):
        return self._api.is_equals(self._ptr, other._ptr)

    def print(self):
        self._api.pr(self._ptr);


def str_status(bool_status):
    return "Ok " if bool_status else "Err"


def test_add_sub():

    rows = 3
    cols = 4

    a_data = [
         1,  2,  3,  4,
         5,  6,  7,  8,
         9, 10, 11, 12,
    ]
    b_data = [
        12, 11, 10,  9,
         8,  7,  6,  5,
         4,  3,  2,  1,
    ]
    c_data = [
        13, 13, 13, 13,
        13, 13, 13, 13,
        13, 13, 13, 13,
    ]

    a = Matrix(rows, cols)
    b = Matrix(rows, cols)
    c = Matrix(rows, cols)

    a.assign(a_data)
    b.assign(b_data)
    c.assign(c_data)
    
    calc = a.add(b)
    is_ok = calc.is_equals(c)
    print("[", str_status(is_ok), "] TEST: A + B")

    calc = c.sub(b)
    is_ok = calc.is_equals(a)
    print("[", str_status(is_ok), "] TEST: A - B")


def test_mul():
    rows = 3;
    cols = 3;

    lhs_data = [
         -4,   5,  -2,
          0,  -7,  11,
          8, -10, -21,
    ]
    rhs_data = [
         2,  3, -5,
        -6, 13, -7,
        12, 15, -6,
    ]
    res_data = [
         -62,   23,  -3,
         174,   74, -17,
        -176, -421, 156,
    ]

    lhs = Matrix(rows, cols)
    rhs = Matrix(rows, cols)
    res = Matrix(rows, cols)

    for i in range(rows):
        for j in range(cols):
            index = i * cols + j
            lhs.set(i, j, lhs_data[index])
            rhs.set(i, j, rhs_data[index])
            res.set(i, j, res_data[index])

    calc = lhs.mul(rhs)
    is_ok = calc.is_equals(res)
    print("[", str_status(is_ok), "] TEST: A * B")


if __name__ == "__main__":
    test_add_sub()
    test_mul()

