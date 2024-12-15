from CitiesMap import *
from itertools import permutations



def all_combs(graph : CitiesMap):
    lenpath = len(graph)
    inds = [i for i in range(lenpath)]

    minDist = float('inf')
    goodPath = []
    for path in permutations(inds):
        existPath = True
        dist = 0
        for i in range(lenpath - 1):
            p = graph[path[i]][path[i + 1]]
            if p != 0:
                dist += p
            else:
                existPath = False
                break

        if graph[path[0]][path[-1]] != 0:
            dist += graph[path[0]][path[-1]]
        else:
            existPath = False

        if existPath:
            print(path, dist)
            if dist < minDist:
                minDist = dist
                goodPath = path[:]

    print(minDist, goodPath)
    return (minDist, goodPath)

if __name__ == '__main__':
    cm = CitiesMap('data/10.csv')
    print(cm)
    cm.draw(indexes=True, show=False)
    all_combs(cm)

