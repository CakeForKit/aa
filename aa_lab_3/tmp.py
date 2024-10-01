import numpy as np
import matplotlib.pyplot as plt

A = [3, 5, 1, 0]
B = [26, 39, 10, 20]

y_pos = np.arange(len(A))
plt.bar(y_pos, B)
plt.xticks(y_pos, A)
plt.title("Animals")
plt.show()