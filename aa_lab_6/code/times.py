import time
import random
import math
import matplotlib.pyplot as plt
from CitiesMap import CitiesMap
from AntAlg import ant_alg
from all_combs import all_combs

COUNT_N_TIME = 5
FILENAME = 'time_data/tdata.txt'
COMMA = ';'

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


def count_time(cmap):
    # print('all_combs')
    tmp_time = []
    i = 0
    while i < COUNT_N_TIME or count_rse(tmp_time) >= 5:
        st = time.process_time_ns()
        all_combs(cmap)
        end = time.process_time_ns()
        tmp_time.append(end - st)
        i += 1
    time_al = sum(tmp_time) / len(tmp_time)

    # print('ant_alg')
    def count_time_ants(days):
        tmp_time = []
        i = 0
        while i < COUNT_N_TIME or count_rse(tmp_time) >= 5:
            st = time.process_time_ns()
            ant_alg(cmap, 0.5, 0.5, days)
            end = time.process_time_ns()
            tmp_time.append(end - st)
            i += 1
        time_ant = sum(tmp_time) / len(tmp_time)
        return time_ant

    all_days = [10, 100, 200]
    times_ant = [count_time_ants(d) for d in all_days]
    return time_al, *times_ant



def see_time():
    for size_graph in range(2, 15):
        fname = f'in_data/tests/graph_size_{size_graph}.csv'
        with open(fname, 'w') as fgraph:
            names = [chr(i) for i in range(65, 65 + size_graph)]
            fgraph.write(',' + ','.join(names) + '\n')
            for i in range(size_graph):
                line = [names[i]] + [str(random.randint(1, 10000)) for _ in range(size_graph)]
                fgraph.write(','.join(line) + '\n')
        cmap = CitiesMap(fname)
        # print(cmap)

        time_al, tants5, tants10, tants20 = count_time(cmap)

        # size_graph time_all_comb time_ants
        # print('size_graph\ttime_all_comb\ttime_ants')
        text = f'{size_graph}{COMMA}{time_al}{COMMA}{tants5}{COMMA}{tants10}{COMMA}{tants20}'
        with open(FILENAME, 'a+') as fdata:
            fdata.write(text + '\n')
        print(text)

def convert_time(s):
    return float(s) * 1e-9

def draw_graph():
    data_lens = []
    data_all_combs = []
    data_ants5 = []
    data_ants10 = []
    data_ants20 = []

    with open(FILENAME) as f:
        line = f.readline()
        while line != '':
            print(line)
            data = list(map(float, line.split(COMMA)))

            data_lens.append(int(data[0]))
            data_all_combs.append(convert_time(data[1]))
            data_ants5.append(convert_time(data[2]))
            data_ants10.append(convert_time(data[3]))
            data_ants20.append(convert_time(data[4]))
            line = f.readline()

    plt.figure(1)
    plt.plot(data_lens, data_all_combs, color='r', marker='.', linestyle='dotted', label='Полный перебор')
    plt.plot(data_lens, data_ants5, color='g', linestyle='solid', label='Муравьиный алгоритм (5 дней)')
    # plt.plot(data_lens, data_ants10, color='b', linestyle='solid', label='Муравьиный алгоритм (10 дней)')
    # plt.plot(data_lens, data_ants20, color='black', linestyle='dotted', label='Муравьиный алгоритм (20 дней)')

    plt.title('Временные характеристики')  # Подпись для оси х
    plt.xlabel('Количество узлов в графе')  # Подпись для оси х
    plt.ylabel('Время, с')  # Подпись для оси y
    plt.legend()

    plt.show()


if __name__ == '__main__':
    # see_time()
    draw_graph()