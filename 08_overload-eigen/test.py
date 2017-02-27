import numpy as np
import example

A = np.array([[1,2,1],
              [2,1,0],
              [-1,1,2]])
B = 10

example.mul(A,B)

A = A.astype(np.int)
B = int(B)

example.mul(A,B)

# print('A                = ',A)
# print('B                = ',B)
# print('')
# print('int:')
# print('example.mul(A,B) = ',example.mul(A.astype(np.int32),int(B)))
# print('A                = ',A)
# print('B                = ',B)
# print('')
# print('double:')
# print('example.mul(A,B) = ',example.mul(A.astype(np.float),float(B)))
# print('A                = ',A)
# print('B                = ',B)

