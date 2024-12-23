from CitiesMap import *
from AntAlg import ant_alg
from all_combs import all_combs
from parameterization import generate_data


if __name__ == '__main__':
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
        print(cm.to_tex())

    # generate_data()


