from CitiesMap import *
from AntAlg import ant_alg
from all_combs import all_combs

def generate_data():
    N = 10
    dirIn = 'in_data'
    dirOut = 'out_data'
    files = [
        (f'{dirIn}/cities{N}_1.csv', f'{dirOut}/cities{N}_1.txt'),
        (f'{dirIn}/cities{N}_2.csv', f'{dirOut}/cities{N}_2.txt'),
        (f'{dirIn}/cities{N}_3.csv', f'{dirOut}/cities{N}_3.txt')
    ]

    for fnames in files:
        fnIn, fnOut = fnames
        cm = CitiesMap(fnIn)
        print(cm)

        lenPathComb, pathComb = all_combs(cm)
        print(f'Comb:', lenPathComb, pathComb)
        print(f'Q = {cm.getDayPheromone()}')

        greedy_list = [0.1, 0.25, 0.5, 0.75, 0.9]
        evaporation_list = greedy_list[:]
        t_max_list = [5, 10, 50, 100, 200]
        COUNT_CANC = 10

        form0 = '<10'
        text = f'{"greedy":{form0}} {"evap":{form0}} {"t_max":{form0}} ' \
               f'{"max_diff":{form0}} {"avg_diff":{form0}} {"mid_diff":{form0}}'
        with open(fnOut, 'w') as f:
            f.write(text + '\n')
        print(text)

        for t_max in t_max_list:
            for evaporation in evaporation_list:
                for greedy in greedy_list:
                    vars = []
                    for i in range(COUNT_CANC):
                        # lenPathAnts, pathAnts = ants_alg(cm, greedy, evaporation, t_max)
                        lenPathAnts, pathAnts = ant_alg(cm, greedy, evaporation, t_max)
                        vars.append(lenPathAnts)
                        # print(f'Ants:', lenPathAnts, pathAnts)
                        # input()

                    diffs = [abs(lenPathComb - v) for v in vars]
                    diffs.sort()
                    max_diff = diffs[-1]
                    n_diff = len(diffs)
                    avg_diff = sum(diffs) / n_diff
                    if n_diff % 2 == 0:
                        mid_diff = (diffs[n_diff // 2] + diffs[n_diff // 2 - 1]) / 2
                    else:
                        mid_diff = diffs[n_diff // 2]

                    form = '<10.2f'
                    text = f'{greedy:{form}} {evaporation:{form}} {t_max:<10} ' \
                           f'{max_diff:{form}} {avg_diff:{form}} {mid_diff:{form}}'
                    with open(fnOut, 'a') as f:
                        f.write(text + '\n')

                    print(text)
                    # print(f'{greedy:{form}} {evaporation:{form}} {t_max:{form}} '
                    #       f'{max_diff:{form}} {avg_diff:{form}} {mid_diff:{form}}')
