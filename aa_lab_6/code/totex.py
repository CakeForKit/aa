

def to_tex():
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
        text = ''
        with open(fnOut, 'r') as f:
            f.readline()
            line = f.readline()
            while line != '':
                param = line.split()
                text += ' & '.join(param) + ' \\\\ \\hline\n'
                line = f.readline()

        with open('tex_tab/' + fnOut.split('/')[1], 'w') as f:
            f.write(text)

def to_csv():
    N = 10
    dirIn = 'in_data'
    dirOut = 'out_data'
    files = [
        (f'{dirIn}/cities{N}_1.csv', f'{dirOut}/cities{N}_1.txt'),
        (f'{dirIn}/cities{N}_2.csv', f'{dirOut}/cities{N}_2.txt'),
        (f'{dirIn}/cities{N}_3.csv', f'{dirOut}/cities{N}_3.txt')
    ]

    i = 1
    for fnames in files:
        fnIn, fnOut = fnames
        with open(fnOut, 'r') as f:
            text = f.read()
        text = text.replace('.', ',')
        with open(f'tex_tab/cities{N}_{i}.csv', 'w') as f:
            f.write(text)
        i += 1

to_csv()
# to_tex()