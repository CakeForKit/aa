from CitiesMap import CitiesMap
import random

class Ant:
    def __init__(self, istart, cmap: CitiesMap, pheromones, greedy):
        self.path = self.generatePath(istart, cmap, pheromones, greedy)
        self.lenPath = self.calcLenPath(cmap, self.path)

    def getPath(self):
        return self.path[:]

    def getLenPath(self):
        return self.lenPath

    def generatePath(self, istart, cmap: CitiesMap, pheromones, greedy, printing=False):
        path = [istart]
        ncities = len(cmap)
        while len(path) != ncities:
            probPaths = [0] * ncities
            for i in range(ncities):
                if i in path:
                    probPaths[i] = 0
                else:
                    ist = path[-1]
                    probPaths[i] = cmap.attractiveness(ist, i) ** greedy * \
                                   pheromones[ist][i] ** (1 - greedy)
                    if printing:
                        print(f'{ist}->{i}: {cmap.attractiveness(ist, i)}**{greedy} * {pheromones[ist][i]}**{1-greedy} = {probPaths[i]}')
            sumProbPaths = sum(probPaths)
            for i in range(ncities):
                probPaths[i] /= sumProbPaths

            if printing:
                print(f'from {path[-1]} greedy={greedy} sum={sumProbPaths}: ', '  '.join([f'{elem:.3f}' for elem in probPaths]))

            r = random.random()
            last = 0
            lines = []
            for i in range(len(probPaths)):
                lines.append((last, last + probPaths[i]))
                last = last + probPaths[i]
            # print(f'probPaths: {probPaths}')
            # print(lines)
            i = 0
            while not( lines[i][0] <= r < lines[i][1] ):
                i += 1
            ind = i


            if printing or ind in path:
                print(f'path: {path}')
                print(f'lines: {list(map(lambda x: f"({x[0]:.2f}, {x[1]:.2f})", lines))}')
                print(f'r={r}, ind = {ind}')
                input()
            path.append(ind)
        return path

    def calcLenPath(self, cmap, path):
        lenPath = 0
        for i in range(len(cmap) - 1):
            lenPath += cmap[path[i]][path[i + 1]]
        lenPath += cmap[path[-1]][path[0]]
        return lenPath

class Pheromones:
    min_ph = 0.01
    def __init__(self, size):
        self.phmap = []
        for i in range(size):
            self.phmap.append([1 for _ in range(size)])
            self.phmap[i][i] = 0

    def __getitem__(self, item):
        return self.phmap[item]

    def update(self, ants, lenBestPath, cmap: CitiesMap, evaporation, printing=False):
        deltaMap = [[0 for i in range(len(cmap))] for _ in range(len(cmap))]

        for a in ants:
            path = a.getPath()
            delta = cmap.day_pheromone / a.getLenPath()
            for i in range(len(path) - 1):
                deltaMap[path[i]][path[i + 1]] += self.phmap[path[i]][path[i + 1]] * (1 - evaporation) + delta
                deltaMap[path[i + 1]][path[i]] = deltaMap[path[i]][path[i + 1]]

                # self.phmap[path[i]][path[i + 1]] = max(self.min_ph, self.phmap[path[i]][path[i + 1]])
            deltaMap[path[0]][path[-1]] += self.phmap[path[i]][path[i + 1]] * (1 - evaporation) + delta
            deltaMap[path[-1]][path[0]] = deltaMap[path[0]][path[-1]]

            if printing:
                print(f'path: {" ".join(map(str, path))}')
                for i in range(len(cmap)):
                    print(" ".join(map(lambda x: f"{x:5.2f}", deltaMap[i])))

        for i in range(len(cmap)):
            for j in range(i):
                self.phmap[i][j] = max(self.min_ph, deltaMap[i][j])
                self.phmap[j][i] = self.phmap[i][j]

        if printing:

            print(f'Pheromones:')
            for i in range(len(cmap)):
                print(' '.join(map(lambda x: f'{float(x):5.2f}', self.phmap[i])))
            input()


def ant_alg(cmap: CitiesMap, greedy, evaporation, t_max):
    bestPath = []
    lenBestPath = float('inf')
    pheromones = Pheromones(len(cmap))

    for t in range(t_max):
        ants = [Ant(i, cmap, pheromones, greedy) for i in range(len(cmap))]
        for a in ants:
            if a.getLenPath() < lenBestPath:
                bestPath = a.getPath()
                lenBestPath = a.getLenPath()
        pheromones.update(ants, lenBestPath, cmap, evaporation)

    return (lenBestPath, bestPath)