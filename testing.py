from ctypes import *
import ctypes
import numpy as np

start = np.ones(2)
end = np.ones(2)
snake = np.ones((900, 2))
length = 5
path = np.ones((900, 2))
bfs = CDLL("./libbfs.so")
print(bfs.bfs(start.ctypes.data_as(ctypes.POINTER(ctypes.c_int)), end.ctypes.data_as(ctypes.POINTER(ctypes.c_int)), snake.ctypes.data_as(ctypes.POINTER(ctypes.c_int)), length, path.ctypes.data_as(ctypes.POINTER(ctypes.c_int))))