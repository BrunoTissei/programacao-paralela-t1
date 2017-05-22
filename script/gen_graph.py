import sys
import math
import matplotlib.pyplot as plt

input_file = open(sys.argv[1], "r")
p, n = map(int, input_file.readline().split())

b_times, s_times = [], []
b_ovrhead, s_ovrhead = [], []
b_speedup, s_speedup = [], []
b_effec, s_effec = [], []
b_sigma, s_sigma = [], []

proc = [x for x in xrange(1, p + 1)]

for i in xrange(p):
    b_tot, s_tot = 0, 0
    b_aux, s_aux = [], []

    for j in xrange(n):
        build, search = map(float, input_file.readline().split())
        b_tot += build
        s_tot += search

        b_aux.append(build)
        s_aux.append(search)

    b_times.append(b_tot / n)
    s_times.append(s_tot / n)

    b_sigma.append(0.0)
    s_sigma.append(0.0)
    for j in xrange(n):
        b_sigma[i] += (b_aux[j] - b_times[i])**2
        s_sigma[i] += (s_aux[j] - s_times[i])**2

    b_sigma[i] = math.sqrt(b_sigma[i] / n)
    s_sigma[i] = math.sqrt(s_sigma[i] / n)


for i in xrange(p):
    b_ovrhead.append((i + 1) * b_times[i] - b_times[0])
    s_ovrhead.append((i + 1) * s_times[i] - s_times[0])

    b_speedup.append(b_times[0] / b_times[i])
    s_speedup.append(s_times[0] / s_times[i])

    b_effec.append(b_speedup[i] / (i + 1))
    s_effec.append(s_speedup[i] / (i + 1))


graphs = ["overhead", "speedup", "efficiency", "avg_time", "std_deviation"]
b_lists = [b_ovrhead, b_speedup, b_effec, b_times, b_sigma]
s_lists = [s_ovrhead, s_speedup, s_effec, s_times, s_sigma]

for i in xrange(len(graphs)):
    plt.plot(proc, b_lists[i], label="Build " + graphs[i])
    plt.plot(proc, s_lists[i], label="Search " + graphs[i])
    plt.xlabel('No. Processors')
    plt.ylabel(graphs[i])

    plt.title(graphs[i])
    plt.legend(loc='best')

    plt.savefig(graphs[i])
    plt.gcf().clear()
