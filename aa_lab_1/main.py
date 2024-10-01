'''
Сравнение алгоритмов:
- Расстояние Левенштейна
    -- рекурсивный
    -- рекурсивный с кешем
    -- матричный
- Дамерау-Левенштейна
'''
import time
import random
import math
import matplotlib.pyplot as plt
from prettytable import PrettyTable


import sys
sys.setrecursionlimit(2000)

COUNT_N_TIME = 10
FILENAME = 'data/data_time.csv'
COMMA = ','

def lev_recurs_(s1, s2, i, j):
    if i == 0:
        return j
    if j == 0:
        return i

    flag = 0 if s1[i - 1] == s2[j - 1] else 1

    variants = [
        lev_recurs_(s1, s2, i, j - 1) + 1,
        lev_recurs_(s1, s2, i - 1, j) + 1,
        lev_recurs_(s1, s2, i - 1, j - 1) + flag
    ]
    return min(variants)


def lev_recurs(s1, s2):
    return lev_recurs_(s1, s2, len(s1), len(s2))


def lev_cache_matrix(s1, s2, i, j, matrix):
    if matrix[i][j] != -1:
        return matrix[i][j]

    if i == 0:
        matrix[i][j] = j
        return j
    if j == 0:
        matrix[i][j] = i
        return i

    flag = 0 if s1[i - 1] == s2[j - 1] else 1
    variants = [
        lev_cache_matrix(s1, s2, i, j - 1, matrix) + 1,
        lev_cache_matrix(s1, s2, i - 1, j, matrix) + 1,
        lev_cache_matrix(s1, s2, i - 1, j - 1, matrix) + flag,
    ]
    matrix[i][j] = min(variants)

    return matrix[i][j]


def lev_cache(s1, s2, printing=False):
    i, j = len(s1), len(s2)
    matrix = []
    for i in range(len(s1) + 1):
        matrix.append([-1] * (len(s2) + 1))

    res = lev_cache_matrix(s1, s2, i, j, matrix)
    if printing:
        for i in range(len(s1) + 1):
            print(matrix[i])
    return res


def lev_mat(s1, s2, printing=False):
    mat = [[i for i in range(len(s2) + 1)]]
    if printing: print(mat[0])
    for i in range(len(s1)):
        mat.append([i + 1])
        i += 1
        for j in range(1, len(s2) + 1):
            flag = 0 if s1[i - 1] == s2[j - 1] else 1
            new = min(
                mat[i][j - 1] + 1,
                mat[i - 1][j] + 1,
                mat[i - 1][j - 1] + flag
            )

            mat[i].append(new)

        if printing: print(mat[i])
    return mat[-1][-1]


def damerau_lev_matrix(s1, s2, i, j, matrix):
    if matrix[i][j] != -1:
        return matrix[i][j]

    if i == 0:
        matrix[i][j] = j
        return j
    if j == 0:
        matrix[i][j] = i
        return i

    flag = 0 if s1[i - 1] == s2[j - 1] else 1
    variants = [
        damerau_lev_matrix(s1, s2, i, j - 1, matrix) + 1,
        damerau_lev_matrix(s1, s2, i - 1, j, matrix) + 1,
        damerau_lev_matrix(s1, s2, i - 1, j - 1, matrix) + flag,
    ]
    if i > 1 and j > 1 and s1[i - 1] == s2[j - 2] and s1[i - 2] == s2[j - 1]:
        variants.append(
            damerau_lev_matrix(s1, s2, i - 2, j - 2, matrix) + 1
        )
    matrix[i][j] = min(variants)

    return matrix[i][j]


def damerau_lev(s1, s2, printing=False):
    i, j = len(s1), len(s2)
    matrix = []
    for i in range(len(s1) + 1):
        matrix.append([-1] * (len(s2) + 1))

    res = damerau_lev_matrix(s1, s2, i, j, matrix)
    if printing:
        for i in range(len(s1) + 1):
            print(matrix[i])
    return res

def count_rse(arr):
    if len(arr) == 0:
        return 100
    n = len(arr)
    avg = sum(arr) / n
    if avg == 0:
        return 0
    s2 = sum([(arr[i] - avg) ** 2 for i in range(n)]) / (n - 1)
    stderr = math.sqrt(s2) / math.sqrt(n)
    rse = (stderr / avg) * 100
    return rse


def count_time(function, s1, s2):
    tmp_time = []
    i = 0
    while i < COUNT_N_TIME or count_rse(tmp_time) >= 5:
        st = time.process_time_ns()
        res = function(s1, s2)
        end = time.process_time_ns()
        tmp_time.append(end - st)  # time_lev_recurs += end - st
        i += 1
    time_lev_recurs = sum(tmp_time) / len(tmp_time)
    return time_lev_recurs, res


def see_time():
    start_len = 1
    end_len = 500
    step = 1
    s1 = ''
    s2 = ''
    with open(FILENAME, 'a+') as f:
        if f.readline() is None: #  or f.readline() == '':
            f.write(f'strs_len{COMMA}time_lev_cache{COMMA}time_lev_matix{COMMA}time_damerau_lev{COMMA}time_lev_recurs\n')

        s1 += ''.join(random.choices('abcdefghijklmnopqrstuvwxyz', k=start_len))
        s2 += ''.join(random.choices('abcdefghijklmnopqrstuvwxyz', k=start_len))
        for l1 in range(start_len, end_len + 1, step):
            f.write(f'{l1}{COMMA}')  # data_lens.append(l1)
            s1 += ''.join(random.choices('abcdefghijklmnopqrstuvwxyz', k=step))
            s2 += ''.join(random.choices('abcdefghijklmnopqrstuvwxyz', k=step))
            print(f'{l1}')
            # print(f'{l1}: s1 = {s1}, s2 = {s2}')

            time_lev_cache, out_lev_cache = count_time(lev_cache, s1, s2)
            f.write(f'{time_lev_cache}{COMMA}')
            print(time_lev_cache, end=' ')

            time_lev_mat, out_lev_mat = count_time(lev_mat, s1, s2)
            f.write(f'{time_lev_mat}{COMMA}')
            print(time_lev_mat, end=' ')

            time_damerau_lev, out_damerau_lev = count_time(damerau_lev, s1, s2)
            f.write(f'{time_damerau_lev}{COMMA}')
            print(time_damerau_lev, end=' ')

            if l1 < 13:
                time_lev_recurs, out_lev_recurs = count_time(lev_recurs, s1, s2)
                f.write(f'{time_lev_recurs}{COMMA}\n')
                print(time_lev_recurs, end=' ')
                print()

                if out_lev_cache != out_lev_mat or out_lev_mat != out_lev_recurs:
                    print(f'{l1}: s1 = {s1}, s2 = {s2}: ', end='')
                    print(f'{out_lev_cache}, {out_lev_mat}, {out_damerau_lev}, {out_lev_recurs}')
                    raise Exception(f'Error in function lev: s1 = {s1}, s2 = {s2}')
            else:
                f.write('\n')
                print()
                if out_lev_cache != out_lev_mat:
                    print(f'{l1}: s1 = {s1}, s2 = {s2}: ', end='')
                    print(f'{out_lev_cache}, {out_lev_mat}, {out_damerau_lev}')
                    raise Exception(f'Error in function lev: s1 = {s1}, s2 = {s2}')


def draw_graph():
    data_lens = []
    data_lev_recurs = []
    data_lev_cache = []
    data_lev_mat = []
    data_damerau_lev = []

    tab = PrettyTable()
    tab.field_names = ['strs_len', 'time_lev_cache', 'time_lev_matix', 'time_damerau_lev', 'time_lev_recurs']

    with open(FILENAME) as f:
        f.readline()
        line = f.readline()
        while line != '':
            data = list(map(float, line.split(COMMA)[:-1]))

            data_lens.append(int(data[0]))
            data_lev_cache.append(float(data[1]))
            data_lev_mat.append(float(data[2]))
            data_damerau_lev.append(float(data[3]))
            if len(data) == 5:
                data_lev_recurs.append(float(data[4]))
                tab.add_row([f'{elem:.3f}' for elem in data])
            else:
                tab.add_row([f'{elem:.3f}' for elem in data] + ['-'])
            line = f.readline()

    print(tab)

    cd = len(data_lev_recurs) - 1
    plt.figure(1)
    plt.plot(data_lens[:cd], data_lev_recurs[:cd], color='r', marker='.', linestyle='dashdot', label='Левенштейн (рекурсивный)')
    plt.plot(data_lens[:cd], data_lev_cache[:cd], color='g', linestyle='dashed', label='Левенштейн (рекурсивный с кешем)')
    plt.plot(data_lens[:cd], data_lev_mat[:cd], color='b', linestyle='solid', label='Левенштейн (матрица)')
    plt.plot(data_lens[:cd], data_damerau_lev[:cd], color='black', linestyle='dotted', label='Дамерау-Левенштейн')
    plt.title('Временные характеристики')  # Подпись для оси х
    plt.xlabel('Длина каждой строки')  # Подпись для оси х
    plt.ylabel('Время, нс')  # Подпись для оси y
    plt.legend()

    plt.figure(2)
    plt.plot(data_lens, data_lev_cache, color='g', linestyle='dashed', label='Левенштейн (рекурсивный с кешем)')
    plt.plot(data_lens, data_lev_mat, color='b', linestyle='solid', label='Левенштейн (матрица)')
    plt.plot(data_lens, data_damerau_lev, color='black', linestyle='dotted', label='Дамерау-Левенштейн')
    plt.title('Временные характеристики')  # Подпись для оси х
    plt.xlabel('Длина каждой строки')  # Подпись для оси х
    plt.ylabel('Время, нс')  # Подпись для оси y
    plt.legend()

    plt.show()




if __name__ == '__main__':
    s2 = '1234'
    s1 = '2134'
    d1 = lev_mat(s1, s2, printing=True)
    d2 = lev_cache(s1, s2, printing=True)
    d3 = damerau_lev(s1, s2, printing=True)
    d4 = lev_recurs(s1, s2)
    print(d1, d2, d3)

    flag = input('Count new? ')
    if 'y' in flag or '1' in flag or '+' in flag:
        see_time()

    draw_graph()
