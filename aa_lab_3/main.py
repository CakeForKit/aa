import random
import matplotlib.pyplot as plt
import numpy as np

# Алгоритм поиска полным перебором.
# Элемента x в массиве arr.
# Возвращает (индекс элемента, кол-во сравнений).
def completeSearch(arr, x, printing=False):
    count_cmp = 0
    for i in range(len(arr)):
        count_cmp += 2
        if arr[i] == x:
            return i, count_cmp
    count_cmp += 1
    return -1, count_cmp


# Алгоритм бинарного поиска.
# Элемента x в массиве arr.
# Возвращает (индекс элемента, кол-во сравнений).
def binSearch(arr, x, printing=False):
    arr.sort()
    n = len(arr)
    if n == 0:
        return -1, 1

    l, r = 0, n - 1
    m = n // 2

    count_cmp = 0
    while arr[m] != x and l <= r:
        count_cmp += 2      # сравнение arr[m] != x and l <= r
        if printing: print(f'{count_cmp}: l={l}({arr[l]}), m={m}({arr[m]}), r={r}({arr[r]}), --> ', end='')
        count_cmp += 1      # сравнение x > arr[m]
        if x > arr[m]:
            l = m + 1
        else:
            r = m - 1
        m = (r + l) // 2
        if printing: print(f'l={l}({arr[l]}), m={m}({arr[m]}), r={r}({arr[r]})')
    count_cmp += 2

    count_cmp += 1
    if l > r:
        return -1, count_cmp
    else:
        return m, count_cmp
    

def completeSearch_tests():
    print('completeSearch: ')
    a = [4, 5, 12, 13, 13, 18, 22, 26, 30, 35]

    arr_x_expInd_expCmp_completeSearch = [
        ([], 4, -1, 1),
        (a, 4, 0, 2),
        (a, 12, 2, 6),
        (a, 35, 9, 20),
        (a, 18, 5, 12)
    ]
    i = 0
    for arr, x, exp_ind, exp_cmp in arr_x_expInd_expCmp_completeSearch:
        ind, count_cmp = completeSearch(arr, x)
        print(f'{i}:', 'OK' if exp_ind == ind and count_cmp == exp_cmp
                else f'ERROR: exp{x, exp_ind, exp_cmp}, get{ind, count_cmp}')
        i += 1

def binSearch_tests(printing=False):
    print('binSearch: ')
    a = [4, 5, 12, 13, 13, 18, 22, 26, 30, 35]

    arr_x_expInd_expCmp_completeSearch = [
        ([], 4, -1, 1),
        (a, 4, 0, 9),   # (l, m, r): (0, 5, 9) -> (0, 2, 4) -> (0, 0, 1)
        (a, 5, 1, 12),
        (a, 35, 9, 12),      # последний элемент
        (a, 18, 5, 3),      # 1 сравнение (л. с.)
        (a, -10, -1, 12),    # элемента нет в массиве    1 сравнение (х. с.)
    ]
    i = 0
    for arr, x, exp_ind, exp_cmp in arr_x_expInd_expCmp_completeSearch:
        ind, count_cmp = binSearch(arr, x, printing)
        print(f'{i}:', 'OK' if exp_ind == ind and count_cmp == exp_cmp
                    else f'ERROR: exp{x, exp_ind, exp_cmp}, get{ind, count_cmp}')
        i += 1


def drawGraphic(len_arr):
    arr = random.sample(range(len_arr), len_arr)

    indexes_of_x = [i for i in range(len_arr)]
    cs_count_cmp = []
    bs_count_cmp = dict()
    bs_count_cmp[-1] = binSearch(arr, -1)[1]
    cs_count_cmp.append(completeSearch(arr, -1)[1])
    for i in range(len_arr):
        ind_cs, count_cmp_cs, = completeSearch(arr, arr[i])
        cs_count_cmp.append(count_cmp_cs)

        ind_bs, count_cmp_bs = binSearch(indexes_of_x, indexes_of_x[i])
        bs_count_cmp[i] = count_cmp_bs

    plt.figure(1)
    plt.bar([-1] + indexes_of_x, cs_count_cmp, width=1)
    plt.title('Полный перебор')  # Подпись для оси х
    plt.xlabel('Индекс элемента в массиве')  # Подпись для оси х
    plt.ylabel('Количество сравнений')  # Подпись для оси y

    plt.figure(2)
    plt.bar(list(bs_count_cmp.keys()), list(bs_count_cmp.values()), width=1)
    plt.title('Бинарный поиск')  # Подпись для оси х
    plt.xlabel('Индекс элемента в массиве')  # Подпись для оси х
    plt.ylabel('Количество сравнений')  # Подпись для оси y

    data_bs = sorted(bs_count_cmp.items(), key=lambda x: x[1])
    indexes = [elem[0] for elem in data_bs]
    cmps = [elem[1] for elem in data_bs]

    plt.figure(3)
    y_pos = np.arange(len(indexes))
    plt.bar(y_pos, cmps, width=0.8)
    plt.xticks(y_pos, indexes)
    plt.title('Бинарный поиск в порядке возрастания количества сранений')  # Подпись для оси х
    plt.xlabel('Индекс элемента в массиве')  # Подпись для оси х
    plt.ylabel('Количество сравнений')  # Подпись для оси y

    plt.show()


def get_len_arr():
    x = 8119
    return int(x / 8 + ((x >> 2) % 10 == 0 if x % 1000 else ((x >> 2) % 10 * (x % 10) + (x >> 1) % 10)))

if __name__ == '__main__':
    len_arr = get_len_arr()
    print(len_arr)
    completeSearch_tests()
    binSearch_tests()
    drawGraphic(len_arr)