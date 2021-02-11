from queue import *
from timeit import default_timer as timer
from collections import defaultdict
import sys

INF = sys.maxsize


class Graph:

    def __init__(self, v):
        self.verticies, self.graph = v, defaultdict(list)

    def add_edge(self, s, d, w):
        self.graph[s].insert(0, [d, w])

    def dijkstra(self, s):
        V, d, p = self.verticies, [], []

        for i in range(self.verticies):
            p.append(-1)

        queue = Queue()

        for vrtc in range(0, self.verticies):

            if vrtc == s:
                d.append(0.0)
                queue.insert(vrtc, 0.0)
            else:

                d.append(INF)
                queue.insert(vrtc, d[vrtc])

        d[s] = 0.0
        queue.decrease_key(tuple([s, 0.0]), d[s])

        while queue.queue_size > 0:
            n_n = queue.pop()
            u = n_n[0]

            for pc in self.graph[u]:
                vrtc = pc[0]

                temp = d[vrtc]

                if queue.check_if_in_heap(vrtc) and d[u] != INF and pc[1] + d[u] < d[vrtc]:
                    d[vrtc], p[vrtc] = pc[1] + d[u], u
                    queue.decrease_key(tuple([vrtc, temp]), d[vrtc])

        print_tab(d, V)

        for i in range(self.verticies):

            if i != s:

                self.print_path(d, p, i)
                print(file=sys.stderr)

    def print_path(self, d, p, j):
        if p[j] == -1:
            print(j, end=' ', file=sys.stderr)
            return

        self.print_path(d, p, p[j])
        print(d[j] - d[p[j]], j, end=' ', file=sys.stderr)


def print_tab(d, n):
    print("V_id \t\t Distance")
    for i in range(n):
        print(i, "\t\t", d[i])


nn = int(input())
ne = int(input())
G = Graph(nn)

for e in range(ne):

    edge = input().split(" ")
    u, v, w = int(edge[0]), int(edge[1]), float(edge[2])
    G.add_edge(u, v, w)

start_v = int(input())

st, t = timer(), 0

G.dijkstra(start_v)

t = timer()
t -= st

print("Time:", t, file=sys.stderr)
