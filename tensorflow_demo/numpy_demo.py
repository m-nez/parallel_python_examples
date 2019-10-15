import numpy as np


if __name__ == "__main__":
    size = 8_000
    max_iter = 100
    np.random.seed(1)
    mat = np.random.uniform(0, 1, (size, size))

    for i in range(max_iter):
        print(i)
        mat *= mat - 1

    print(np.mean(mat))
