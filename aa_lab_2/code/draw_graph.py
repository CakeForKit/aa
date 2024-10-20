import matplotlib.pyplot as plt
from prettytable import PrettyTable



def draw_graph(filename, comma):
    data_sizes_0, data_sizes_1 = [], []
    std_0, std_1 = [], []
    vin_0, vin_1 = [], []
    nvin_0, nvin_1 = [], []

    tab0 = PrettyTable()
    tab0.field_names = ['sizem', 'std', 'vin', 'new_vin']
    tab1 = PrettyTable()
    tab1.field_names = ['sizem', 'std', 'vin', 'new_vin']

    with open(filename) as f:
        f.readline()
        line = f.readline()
        num = 0
        while line != '':
            data = list(map(float, line.split(comma)[:-1]))

            if num % 2 != 0:
                data_sizes_0.append(int(data[0]))
                std_0.append(int(data[1]))
                vin_0.append(float(data[2]))
                nvin_0.append(float(data[3]))
                tab0.add_row([f'{elem}' for elem in data])
            else:
                data_sizes_1.append(int(data[0]))
                std_1.append(int(data[1]))
                vin_1.append(float(data[2]))
                nvin_1.append(float(data[3]))

                tab1.add_row([f'{elem}' for elem in data])
            line = f.readline()
            num += 1

    print(tab0)
    print(tab1)

    plt.figure(1)
    plt.plot(data_sizes_0, std_0, color='r', marker='.', linestyle='dashdot', label='Стандартный алгоритм')
    plt.plot(data_sizes_0, vin_0, color='g', linestyle='dashed', label='Алгоритм Винограда')
    plt.plot(data_sizes_0, nvin_0, color='b', linestyle='solid', label='Оптимизированный алгоритм Винограда')
    plt.title('Временные характеристики при четных размерах матрицы')  # Подпись для оси х
    plt.xlabel('Размер квадратной матрицы')  # Подпись для оси х
    plt.ylabel('Время, нс')  # Подпись для оси y
    plt.legend()

    plt.figure(2)
    plt.plot(data_sizes_1, std_1, color='r', marker='.', linestyle='dashdot', label='Стандартный алгоритм')
    plt.plot(data_sizes_1, vin_1, color='g', linestyle='dashed', label='Алгоритм Винограда')
    plt.plot(data_sizes_1, nvin_1, color='b', linestyle='solid', label='Оптимизированный алгоритм Винограда')
    plt.title('Временные характеристики при нечетных размерах матрицы')  # Подпись для оси х
    plt.xlabel('Размер квадратной матрицы')  # Подпись для оси х
    plt.ylabel('Время, нс')  # Подпись для оси y
    plt.legend()

    plt.figure(3)
    # plt.plot(data_sizes_0, std_0, color='r', marker='.', linestyle='dashdot', label='Стандартный алгоритм')
    plt.plot(data_sizes_0, vin_0, color='g', linestyle='dashed', label='Алгоритм Винограда')
    plt.plot(data_sizes_0, nvin_0, color='b', linestyle='solid', label='Оптимизированный алгоритм Винограда')
    plt.title('Временные характеристики при четных размерах матрицы')  # Подпись для оси х
    plt.xlabel('Размер квадратной матрицы')  # Подпись для оси х
    plt.ylabel('Время, нс')  # Подпись для оси y
    plt.legend()

    plt.figure(4)
    # plt.plot(data_sizes_1, std_1, color='r', marker='.', linestyle='dashdot', label='Стандартный алгоритм')
    plt.plot(data_sizes_1, vin_1, color='g', linestyle='dashed', label='Алгоритм Винограда')
    plt.plot(data_sizes_1, nvin_1, color='b', linestyle='solid', label='Оптимизированный алгоритм Винограда')
    plt.title('Временные характеристики при нечетных размерах матрицы')  # Подпись для оси х
    plt.xlabel('Размер квадратной матрицы')  # Подпись для оси х
    plt.ylabel('Время, нс')  # Подпись для оси y
    plt.legend()

    plt.show()


if __name__ == '__main__':
    filename = 'data/good_data.csv'
    draw_graph(filename, ',')
