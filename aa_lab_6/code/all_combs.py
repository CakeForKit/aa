from itertools import permutations
from CitiesMap import *

def all_combs(graph : CitiesMap):
    lenpath = len(graph)
    inds = [i for i in range(1, lenpath)]

    minDist = float('inf')
    goodPath = []
    for path in permutations(inds):
        path = [0] + list(path)
        dist = 0
        for i in range(lenpath - 1):
            dist += graph[path[i]][path[i + 1]]
        dist += graph[path[0]][path[-1]]

        if dist < minDist:
            minDist = dist
            goodPath = path[:]

    return (minDist, goodPath)

