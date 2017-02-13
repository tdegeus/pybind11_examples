import numpy as np
import example

A     = np.arange(10)

print('allocate:')
print('A         ->',A)

array = example.CustomVectorXd(A)

print('call 1:')
print('A         ->',A)
print('array.mul -> ',array.mul())

print('call 1:')
print('A         ->',A)
print('array.mul -> ',array.mul(factor=100))

B     = example.trans(A)

print('call 3:')
print('A         ->',A)
print('B         ->',B)
