
import numpy as np
import example

A_list  = [0,1,2,3,4,5]
A_numpy = np.arange(10)

print('A_list  = ',A_list )
print('A_numpy = ',A_numpy)

B_list  = example.multiply(A_list )
B_numpy = example.multiply(A_numpy)

print('----------')
print('A_list  = ',A_list )
print('A_numpy = ',A_numpy)
print('B_list  = ',B_list )
print('B_numpy = ',B_numpy)


