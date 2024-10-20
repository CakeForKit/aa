import time
import random
import math


def print_matrix(mat):
    print('Matrix:')
    for row in mat:
        print(' '.join(f'{val:5.0f}' for val in row))


def standard_matrix_mul(mat1, rows1, cols1, mat2, rows2, cols2, res):
    for i in range(rows1):
        for j in range(cols2):
            res[i][j] = 0
            for k in range(cols1):
                res[i][j] += mat1[i][k] * mat2[k][j]


def vinograd_matrix_mul(mat1, rows1, cols1, mat2, rows2, cols2, res):
    help_mat1 = [0] * rows1
    help_mat2 = [0] * cols2

    for i in range(rows1):
        for j in range(cols1 // 2):
            help_mat1[i] += mat1[i][2 * j] * mat1[i][2 * j + 1]

    for i in range(cols2):
        for j in range(cols1 // 2):
            help_mat2[i] += mat2[2 * j][i] * mat2[2 * j + 1][i]

    for i in range(rows1):
        for j in range(cols2):
            res[i][j] = -help_mat1[i] - help_mat2[j]
            for k in range(cols1 // 2):
                res[i][j] += (mat1[i][2 * k] + mat2[2 * k + 1][j]) * (mat1[i][2 * k + 1] + mat2[2 * k][j])

    if cols1 % 2 != 0:
        for i in range(rows1):
            for j in range(cols2):
                res[i][j] += mat1[i][-1] * mat2[-1][j]


def new_vinograd_matrix_mul(mat1, rows1, cols1, mat2, rows2, cols2, res):
    help_mat1 = [0] * rows1
    help_mat2 = [0] * cols2

    for i in range(rows1):
        for j in range(1, cols1, 2):
            help_mat1[i] -= mat1[i][j - 1] * mat1[i][j]

    for i in range(cols2):
        for j in range(1, cols1, 2):
            help_mat2[i] -= mat2[j - 1][i] * mat2[j][i]

    for i in range(rows1):
        for j in range(cols2):
            res[i][j] = help_mat1[i] + help_mat2[j]
            for k in range(1, cols1, 2):
                res[i][j] += (mat1[i][k - 1] + mat2[k][j]) * (mat1[i][k] + mat2[k - 1][j])
            if cols1 % 2 != 0:
                res[i][j] += mat1[i][-1] * mat2[-1][j]


def matrix_mul(m1, m2, func):
    rows1, rows2 = len(m1), len(m2)
    if rows1 == 0 or rows2 == 0:
        return []

    cols1, cols2 = len(m1[0]), len(m2[0])
    if cols1 == 0 or cols2 == 0 or cols1 != rows2:
        return []

    res = [[0] * cols2 for _ in range(rows1)]
    func(m1, rows1, cols1, m2, rows2, cols2, res)
    return res

def count_time(function, m1, m2, count_n_time=10):
    tmp_time = []
    i = 0
    while i < count_n_time:
        start_time = time.ticks_ms() # микросекунды us
        matrix_mul(m1, m2, function)
        end_time = time.ticks_ms()
        tmp_time.append(end_time - start_time)
        i += 1

    return sum(tmp_time) / len(tmp_time)


def see_time(comma):
    k = 4
    start_len = 10 * k + 1
    end_len = 10 * (k + 1)
    step = 1
    mat1 = []
    mat2 = []

    for l1 in range(start_len, end_len + 1, step):
        print(f'{l1}{comma}', end='')  # data_lens.append(l1)
        mat1 = [[random.randint(10, 99) for _ in range(l1)] for __ in range(l1)]
        mat2 = [[random.randint(10, 99) for _ in range(l1)] for __ in range(l1)]
        # print(f'{l1}: ', end='')
        # print_matrix(mat1)
        # print_matrix(mat2)
        # print('time: ')

        std_time = count_time(standard_matrix_mul, mat1, mat2)
        print(f'{std_time}{comma}', end='')
        # print(std_time, end='')

        vin_time = count_time(vinograd_matrix_mul, mat1, mat2)
        print(f'{vin_time}{comma}', end='')
        # print(vin_time, end='')

        nvin_time = count_time(new_vinograd_matrix_mul, mat1, mat2)
        print(f'{nvin_time}{comma}')
        # print(nvin_time)

if __name__ == '__main__':
    # print('werewrewr')
    see_time(',')
