import numpy as np
import example

A     = np.arange(10)

print('allocate:')
print('A         ->',A)

array = example.CustomVectorXd(A)

print('call 1:')
print('array.mul -> ',array.mul(100))
print('A         ->',A)

B     = example.trans(A)

print('call 2:')
print('B         ->',B)
print('A         ->',A)
