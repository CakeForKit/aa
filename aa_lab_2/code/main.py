from draw_graph import draw_graph

def print_matrix(mat, n=''):
    print(f'Matrix{n}:')
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


''' Вариант: 
инкремент счётчика наиболее вложенного цикла на 2;                  done
объединение III и IV частей алгоритма Винограда; 
введение декремента при вычислении вспомогательных массивов;'''
def new_vinograd_matrix_mul(mat1, rows1, cols1, mat2, rows2, cols2, res):
    help_mat1 = [0] * rows1
    help_mat2 = [0] * cols2

    for i in range(rows1):
        for j in range(1, cols1, 2):
            help_mat1[i] -= mat1[i][j - 1] * mat1[i][j]  # 1+1+3+2+2=9

    for i in range(cols2):
        for j in range(1, cols1, 2):
            help_mat2[i] -= mat2[j - 1][i] * mat2[j][i]

    for i in range(rows1):
        for j in range(cols2):
            res[i][j] = help_mat1[i] + help_mat2[j]  # 2+1+1+1+1

            for k in range(1, cols1, 2):
                res[i][j] = res[i][j] + \
                            (mat1[i][k - 1] + mat2[k][j]) * \
                            (mat1[i][k] + mat2[k - 1][j])  # 2+1+2+1+3+2+2+2+1+3=19

            if cols1 % 2 != 0:
                res[i][j] = res[i][j] + mat1[i][-1] * mat2[-1][j]  # 2+1+2+1+2+2+2=12


def matrix_mul(m1, m2, func):
    rows1, rows2 = len(m1), len(m2)
    if rows1 == 0 or rows2 == 0:
        return []
    cols1, cols2 = len(m1[0]), len(m2[0])
    if cols1 == 0 or cols2 == 0:
        return []

    if cols1 != rows2:
        return []

    if rows1 == cols1 and rows1 == 1:
        return [[m1[0][0] * m2[0][0]]]
    res = [[0] * cols2 for _ in range(rows1)]

    func(m1, rows1, cols1, m2, rows2, cols2, res)
    return res


def cmp_mul(mat1, mat2):
    std_res = matrix_mul(mat1, mat2, standard_matrix_mul)
    vin_res = matrix_mul(mat1, mat2, vinograd_matrix_mul)
    nvin_res = matrix_mul(mat1, mat2, new_vinograd_matrix_mul)
    # print_matrix(std_res)
    return std_res == vin_res and vin_res == nvin_res


def test_mul():
    ind = 0

    m1 = [[]]
    m2 = [[]]
    if not cmp_mul(m1, m2):
        print('ERROR:', ind)
    ind += 1

    m1 = [[1]]
    m2 = [[2]]
    if not cmp_mul(m1, m2):
        print('ERROR:', ind)
    ind += 1

    m1 = [[2, 3],
          [4, 5],
          [6, 7]]
    m2 = [[10, 11, 12],
          [20, 21, 23]]
    if not cmp_mul(m1, m2):
        print('ERROR:', ind)
    ind += 1

    m1 = [[67, 78, 45],
          [75, 96, 77],
          [85, 96, 19]]
    m2 = [[73, 20, 46],
          [10, 74, 93],
          [42, 20, 39]]
    if not cmp_mul(m1, m2):
        print('ERROR:', ind)
    ind += 1

    print('END TESTS')


def menu():
    print(f'{GRAPH} - Вывести графики зависимости работы алгоритмов от размера матриц\n'
          f'{PERSON} - Умножение матриц\n'
          f'{TEST} - Тестирование алгоритмов\n'
          f'{END} - Выход\n')


GRAPH = '1'
PERSON = '2'
TEST = '3'
END = '0'
# MODE = GRAPH

if __name__ == '__main__':

    menu()
    mode = input('Введите действие: ')
    while mode != END:
        if mode == TEST:
            test_mul()
        elif mode == GRAPH:
            filename = 'data/good_data.csv'
            draw_graph(filename, ',')
        elif mode == PERSON:
            try:
                r1, c1 = map(int, input('Введите размер матрицы 1: ').split())
                m1 = [[0] * c1 for _ in range(r1)]
                print(f'Введите матрицу размером {r1}x{c1}')
                for i in range(r1):
                    inp = list(map(float, input().strip().split()))
                    for j in range(c1):
                        m1[i][j] = inp[j]

                r2, c2 = map(int, input('Введите размер матрицы 2: ').split())
                m2 = [[0] * c2 for _ in range(r2)]
                print(f'Введите матрицу размером {r2}x{c2}')
                for i in range(r2):
                    inp = list(map(float, input().strip().split()))
                    for j in range(c2):
                        m2[i][j] = inp[j]

                print_matrix(m1, '1')
                print_matrix(m2, '2')
                print_matrix(matrix_mul(m1, m2, new_vinograd_matrix_mul), 'Res')
            except Exception:
                print('ERROR: Ошибка ввода')
        else:
            print('ERROR: Неизвестное значение параметра MODE')

        menu()
        mode = input('Введите действие: ')

# See PyCharm help at https://www.jetbrains.com/help/pycharm/
