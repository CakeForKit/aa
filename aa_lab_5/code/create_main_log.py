
COUNT_PAIRS = 500

logBeg = r"""\begin{longtable}{|
		>{\raggedright\arraybackslash}p{.2\textwidth - 2\tabcolsep}|
		>{\raggedright\arraybackslash}p{.2\textwidth - 2\tabcolsep}|
		>{\raggedright\arraybackslash}p{.3\textwidth - 2\tabcolsep}|
		>{\raggedright\arraybackslash}p{.3\textwidth - 2\tabcolsep}|
	}
	\caption{Функциональные тесты}\label{tbl:tests} \\\hline
	№ заявки & № потока & время начала обслучивания заявки & время конца обслуживания заявки \\\hline
	\endfirsthead
	\caption{Функциональные тесты (продолжение)} \\\hline
	№ заявки & № потока & время начала обслучивания заявки & время конца обслуживания заявки \\\hline                    
	\endhead
	\endfoot
	"""
logEnd = r"""
\end{longtable}"""

need = r"""
	0 & 1 & 249 & 270 \\\hline
	0 & 1 & 249 & 270 \\\hline
"""


# tstart=249        tend=270        request=0    thread=1

def create_table_log():
    tabstr = ''
    filename = 'log/log.txt'
    with open(filename, 'r') as f:
        line = f.readline()
        while line != '':
            d = line.split('=')
            ts, te, req, thr = d[1].split()[0], d[2].split()[0], d[3].split()[0], d[4].split()[0]
            s = rf'{req} & {thr} & {ts} & {te} \\\hline' + '\n'

            tabstr += s

            line = f.readline()
    table = logBeg + tabstr + logEnd
    fileout = 'log/tex_table_log.txt'
    with open(fileout, 'w') as f:
        f.write(table)

def get_statistic():
    goods = ''
    with open(f'log/{goods}p1_log.txt', 'r') as f1:
        with open(f'log/{goods}p2_log.txt', 'r') as f2:
            with open(f'log/{goods}p3_log.txt', 'r') as f3:
                lines = [f1.readline(), f2.readline(), f3.readline()]

                exist_time, q2_time, q3_time, thr1_time, thr2_time, thr3_time = [], [], [], [], [], []
                while lines[0] != '':
                    times = [(int(elem[0]), int(elem[1])) for elem in [line.split() for line in lines]]
                    # print(times)

                    exist_time.append(times[-1][-1] - times[0][0])
                    q2_time.append(times[1][0] - times[0][1])
                    q3_time.append(times[2][0] - times[1][1])
                    thr1_time.append(times[0][1] - times[0][0])
                    thr2_time.append(times[1][1] - times[1][0])
                    thr3_time.append(times[2][1] - times[2][0])

                    lines = [f1.readline(), f2.readline(), f3.readline()]

                print('avg exist_time =', sum(exist_time) / len(exist_time))
                print('avg q2_time =', sum(q2_time) / len(q2_time))
                print('avg q3_time =', sum(q3_time) / len(q3_time))
                print('avg thr1_time =', sum(thr1_time) / len(thr1_time))
                print('avg thr2_time =', sum(thr2_time) / len(thr2_time))
                print('avg thr3_time =', sum(thr3_time) / len(thr3_time))


if __name__ == '__main__':
    cnt1 = cnt2 = cnt3 = 0

    fn = []
    for n in [1, 2, 3]:
        fn.append(f'log/p{n}_log.txt')
    with open(fn[0], 'r') as f1:
        with open(fn[1], 'r') as f2:
            with open(fn[2], 'r') as f3:
                with open('log/log.txt', 'w') as fout:
                    line1 = f1.readline()
                    t1 = list(map(int, line1.split()))
                    t1 = [t1[0], 1, t1[1]]
                    line2 = f2.readline()
                    t2 = list(map(int, line2.split()))
                    t2 = [t2[0], 2, t2[1]]
                    line3 = f3.readline()
                    t3 = list(map(int, line3.split()))
                    t3 = [t3[0], 3, t3[1]]
                    # fout.write(f"start_time = {start_time}\n")

                    while line1 != '' or line2 != '' or line3 != '':
                        mmin = min([t1, t2, t3])
                        # print(f'{[t1, t2, t3]} -> {mmin}')
                        if t1 == mmin:
                            num = 1
                            request = cnt1
                            cnt1 += 1
                            line1 = f1.readline()
                            if line1 == '':
                                t1 = [float('inf'), float('inf')]
                            else:
                                t1 = list(map(int, line1.split()))
                                t1 = [t1[0], 1, t1[1]]
                        elif t2 == mmin:
                            num = 2
                            request = cnt2
                            cnt2 += 1
                            line2 = f2.readline()
                            if line2 == '':
                                t2 = [float('inf'), float('inf')]
                            else:
                                t2 = list(map(int, line2.split()))
                                t2 = [t2[0], 2, t2[1]]
                        elif t3 == mmin:
                            num = 3
                            request = cnt3
                            cnt3 += 1
                            line3 = f3.readline()
                            if line3 == '':
                                t3 = [float('inf'), float('inf')]
                            else:
                                t3 = list(map(int, line3.split()))
                                t3 = [t3[0], 3, t3[1]]

                        fout.write(f'tstart={mmin[0]:<10.0f} tend={mmin[2]:<10.0f} request={request:<4.0f} thread={num}\n')

    get_statistic()
    create_table_log()
