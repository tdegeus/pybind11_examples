import numpy as np
import example

A = np.array([[1,2,1],
              [2,1,0],
              [-1,1,2]])

print('A = \n'             ,A)
print('example.det(A) = \n',example.det(A))
print('example.inv(A) = \n',example.inv(A))

