
def print_matrix(mat):
    print('Matrix:')
    for i in range(len(mat)):
        for j in range(len(mat[0])):
            # print('[')
            print(f'{mat[i][j]:5.0f}', end=' ')
        print()

def standard_matrix_mul(mat1, rows1, cols1, mat2, rows2, cols2, res):
    for i in range(rows1):
        for j in range(cols2):  # cols1 == rows2
            res[i][j] = 0
            for k in range(cols1):
                res[i][j] = res[i][j] + mat1[i][k] * mat2[k][j]
            # print(f'res[{i}][{j}] = {res[i][j]}')


def vinograd_matrix_mul(mat1, rows1, cols1, mat2, rows2, cols2, res):
    help_mat1 = [0] * rows1
    help_mat2 = [0] * cols2

    for i in range(rows1):
        for j in range(cols1 // 2):
            help_mat1[i] = help_mat1[i] + mat1[i][2 * j] * mat1[i][2 * j + 1]

    for i in range(cols2):
        for j in range(cols1 // 2):
            help_mat2[i] = help_mat2[i] + mat2[2 * j][i] * mat2[2 * j + 1][i]

    for i in range(rows1):
        for j in range(cols2):
            res[i][j] = -help_mat1[i] - help_mat2[j]

            for k in range(cols1 // 2):
                res[i][j] = res[i][j] + \
                            (mat1[i][2 * k] + mat2[2 * k + 1][j]) * \
                            (mat1[i][2 * k + 1] + mat2[2 * k][j])

    if cols1 % 2 != 0:
        for i in range(rows1):
            for j in range(cols2):
                res[i][j] = res[i][j] + mat1[i][-1] * mat2[-1][j]


def matrix_mul(m1, m2, func):
    rows1, cols1 = len(m1), len(m1[0])
    rows2, cols2 = len(m2), len(m2[0])

    if cols1 != rows2:
        return []

    res = [[0] * cols2 for _ in range(rows1)]

    func(m1, rows1, cols1, m2, rows2, cols2, res)
    return res


if __name__ == '__main__':
    mat1 = [
        [2, 3],
        [4, 5],
        [6, 7]
    ]
    mat2 = [
        [10, 11, 12],
        [20, 21, 23]
    ]

    std_res = matrix_mul(mat1, mat2, standard_matrix_mul)
    vin_res = matrix_mul(mat1, mat2, vinograd_matrix_mul)
    print_matrix(std_res)
    print_matrix(vin_res)


# See PyCharm help at https://www.jetbrains.com/help/pycharm/
