import numpy as np
import example

A = np.array([[1,2,1],
              [2,1,0],
              [-1,1,2]])
B = 10

print(example.mul(A.astype(np.int  ),int  (B)))
print(example.mul(A.astype(np.float),float(B)))
