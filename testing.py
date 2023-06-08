from ctypes import *
import numpy as np


bfs = CDLL("./testing.so")
# b = pointer(pointer(pointer(c_int())))
# b = POINTER(900 * POINTER(900 * POINTER(2 * c_int)))
# bfs.gameSim.argtypes = [POINTER(900 * POINTER(900 * POINTER(2 * c_int)))]
# c = b(pointer(pointer(c_int(42))), pointer(pointer(c_int(38))))
# a.func(c)
# datatypes
# a = c_int * (900 * 450 * 2)
a = c_int
# aa = POINTER(a) * 900
# aaa = POINTER(aa) * 900

# variables
# b = aaa(pointer(aa(pointer(a(3, 21)))))
# print(b[0][0][0][][0]) # deref, deref, ?, deref, 900*900 index, 2 index
# arr = a()
# length = bfs.gameSim(arr)
# for row_index in range(length):
#     for col_index in range(row_index):
#         print("(" + str(arr[int(row_index * (row_index + 1) / 2 + col_index) * 2]) + " " + str(arr[int(row_index * (row_index + 1) / 2 + col_index) * 2 + 1]), end=") ")
#     print("")
# for 2d triangle array you can do ((rowIndex) * (rowIndex + 1)) / 2 + colIndex
# bb = aa(pointer(b))
# bbb = aaa(pointer(bb))
# bbbb = aaaa(pointer(bbb))

# arr = aa(pointer(a(3, 21)))
# print(b[0][0][0][0][0][0])
# print(b[0][0][0][0][0][1])

# print(bbbb[0][1][0])
# print(bbbb[0][1][1])

for i in range(10):
    print(bfs.func(a(i)))