import random

FILENAME = 'data_in/data_in.txt'
LENSTR = 3 # 10
MAXINT = 99
COUNT = 500

def gen(map, len_key, maxint, count):
    letters = 'abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789'
    while (len(map.keys()) < count):
        key = ''.join(random.choice(letters) for i in range(len_key))
        num = random.randint(0, maxint)
        map[key] = num

if __name__ == '__main__':
    map = dict()
    gen(map, LENSTR, MAXINT, COUNT)

    with open(FILENAME, 'w') as file:
        for key, num in map.items():
            s = f'{key} : {num}\n'
            file.write(s)
            print(s, end='')
