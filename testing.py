from ctypes import *
import numpy as np


a = CDLL("./libtest.so")
# b = pointer(pointer(pointer(c_int())))
# b = POINTER(900 * POINTER(900 * POINTER(2 * c_int)))
# a.func.argtypes = [POINTER(900 * POINTER(900 * POINTER(2 * c_int)))]
# c = b(pointer(pointer(c_int(42))), pointer(pointer(c_int(38))))
# a.func(c)
a = c_int * 2
aa = POINTER(a) * 900
arr = aa(pointer(a(3, 21)))
print(arr[0][0][0])
print(arr[0][0][1])

print(arr[0][1][0])
print(arr[0][1][1])