import matplotlib.pyplot as plt


def draw_graph(filename, split_by):
    data_triangles = []
    pTh = [0, 1, 2, 4, 8, 16, 32]
    data_pTh = [[] for _ in range(len(pTh))]

    with open(filename) as f:
        f.readline()
        line = f.readline()
        while line != '':
            data = list(map(float, line.split(split_by)[:]))

            data_triangles.append(int(data[0]))
            for i in range(len(pTh)):
                data_pTh[i].append(int(data[i + 1]))
            line = f.readline()

    for i in range(len(pTh)):
        print(data_pTh[i])

    plt.figure(1)
    plt.plot(data_triangles[:], data_pTh[0], color='r', linestyle='solid', label='без дополнительных потоков')
    plt.plot(data_triangles[:], data_pTh[1], color='g', linestyle='dotted', label='1 дополнительный поток')
    plt.plot(data_triangles[:], data_pTh[2], color='b', linestyle='dashed', label='2 дополнительных потока')
    plt.plot(data_triangles[:], data_pTh[3], color='black', linestyle='dashdot', label='4 дополнительный поток')
    plt.plot(data_triangles[:], data_pTh[4], color='c', marker='.', label='8 дополнительных потока')
    plt.plot(data_triangles[:], data_pTh[5], color='m', marker='v', label='16 дополнительных потока')
    plt.plot(data_triangles[:], data_pTh[6], color='y', marker='*', label='32 дополнительных потока')
    plt.title('Зависимость времени отрисовки сцены от количества треугольных полигонов на сцене')  # Подпись для оси х
    plt.xlabel('Количество треугольных полигонов на сцене')  # Подпись для оси х
    plt.ylabel('Время, мкс')  # Подпись для оси y
    plt.legend()
    plt.show()


draw_graph('data_time/dataTime.txt', '\t')