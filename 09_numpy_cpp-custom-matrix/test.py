
import numpy as np
import example

A = np.arange(5)
B = np.arange(5)

print(example.mul(A,B))

A = np.arange(25).reshape(5,5)
B = np.arange(25).reshape(5,5)

print(example.mul(A,B))

A = np.arange(125).reshape(5,5,5)
B = np.arange(125).reshape(5,5,5)

print(example.mul(A,B))
