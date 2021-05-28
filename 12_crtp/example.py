import mymodule
import numpy as np

A = np.array([1, 2, 3])

assert np.all(mymodule.Base().myfunc(A) == 2 * A)
assert np.all(mymodule.Derived().myfunc(A) == 3 * A)
