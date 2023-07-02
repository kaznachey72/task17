#!/usr/bin/env python3

from ctypes import c_size_t, c_bool, c_void_p, c_char_p, Structure, POINTER, byref, cdll, string_at


class value_t(Structure):
    _fields_ = [("data", c_char_p), ("len", c_size_t)]


class WrapperStack(object):
    def __init__(self):
        self.lib_cstack = cdll.LoadLibrary("libcstack.so")

        # value_t make_value(char *data, size_t len);
        self.make_value = self.lib_cstack.make_value
        self.make_value.argtypes = [c_char_p, c_size_t]
        self.make_value.restype = value_t

        # value_t copy_value(char *data, size_t len);
        self.copy_value = self.lib_cstack.copy_value
        self.copy_value.argtypes = [c_char_p, c_size_t]
        self.copy_value.restype = value_t

        # void free_value(value_t *value);
        self.free_value = self.lib_cstack.free_value
        self.free_value.argtypes = [POINTER(value_t)]

        # cstack_t *cstack_new();
        self.new = self.lib_cstack.cstack_new
        self.new.argtypes = []
        self.new.restype = c_void_p

        # void cstack_del(cstack_t *cstack);
        self.delete = self.lib_cstack.cstack_del
        self.delete.argtypes = [c_void_p]

        # void cstack_ctor(cstack_t *cstack, size_t capacity);
        self.ctor = self.lib_cstack.cstack_ctor
        self.ctor.argtypes = [c_void_p, c_size_t]

        # void cstack_dtor(cstack_t *cstack, deleter_t deleter);
        self.dtor = self.lib_cstack.cstack_dtor
        self.dtor.argtypes = [c_void_p, c_void_p]

        # bool cstack_push(cstack_t *cstack, value_t value);
        self.push = self.lib_cstack.cstack_push
        self.push.argtypes = [c_void_p, value_t]
        self.push.restype = c_bool

        # bool cstack_pop(cstack_t *cstack, value_t *value);
        self.pop = self.lib_cstack.cstack_pop
        self.pop.argtypes = [c_void_p, POINTER(value_t)]
        self.pop.restype = c_bool

        # size_t cstack_size(const cstack_t *cstack);
        self.size = self.lib_cstack.cstack_size
        self.size.argtypes = [c_void_p]
        self.size.restype = c_size_t

        # void cstack_clear(cstack_t *cstack, deleter_t);
        self.clear = self.lib_cstack.cstack_clear
        self.clear.argtypes = [c_void_p, c_void_p]


class Stack(object):
    def __init__(self, capacity):
        self._api = WrapperStack()
        self._ptr = self._api.new()
        self._api.ctor(self._ptr, capacity)

    def __del__(self):
        self._api.dtor(self._ptr, self._api.free_value)
        self._api.delete(self._ptr)

    def size(self):
        return self._api.size(self._ptr)

    def push(self, item):
        result = self._api.push(self._ptr, self._api.copy_value(item.encode('utf-8'), len(item)));
        if not result:
            raise Exception("stack is full!")

    def pop(self):
        value = value_t()
        result = self._api.pop(self._ptr, byref(value))
        if not result:
            raise Exception("stack is empty!")
        item = string_at(value.data, value.len).decode('utf-8')
        self._api.free_value(value)
        return item

    def clear(self):
        self._api.clear(self._ptr, self._api.free_value)


if __name__ == "__main__":
    str_values = ["aaaaa", "bbbbb", "ccccc", "ddddd", "eeeee", "fffff"]
    size = len(str_values)

    capacity = 100;
    stack = Stack(capacity)
    print("stack create", f"capacity: {capacity}", f"size: {size}", sep='\n', end='\n\n')


    for value in str_values:
        stack.push(value)
        print("push item:", value, end='\t')
        print("size after push:", stack.size())
    print()


    while stack.size() > 0:
        print("pop item: ", stack.pop(), end='\t')
        print("size after pop: ", stack.size())
    print()


    stack.clear();
    print("size after clear:", stack.size())
    print()
