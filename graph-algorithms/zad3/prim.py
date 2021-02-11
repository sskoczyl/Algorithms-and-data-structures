from collections import defaultdict
import sys
from queue import Queue


class Graph:
    def __init__(self, v):
        self.verticies, self.G = v, defaultdict(list)

    def add_edge(self, s, d, w):
        self.G[s].insert(0, [d, w])


def prim(G):
    s, d, p = 1, [], []

    for i in range(G.verticies):
        p.append(-1)

    queue = Queue()

    for v in range(0, G.verticies):
        if v == s:
            d.append(0.0)
            queue.insert(v, 0.0)
        else:
            d.append(sys.maxsize)
            queue.insert(v, d[v])

    st, ts = list(), 0
    st.append(s)

    while not queue.is_empty():
        n = queue.pop()
        u = n[0]

        for w in G.G[u]:
            v = w[0]
            temp = d[v]
            if queue.check_if_in_heap(v) and d[u] != sys.maxsize and w[1] + d[u] < d[v]:
                d[v], p[v] = w[1] + d[u], u

                if v not in st:
                    st.append(v)
                    ts += d[v]

                    print(u, v, d[v] - d[u])

                queue.decrease_key(tuple([v, temp]), d[v])
    print(ts)


nn = int(input())
ne = int(input())
G = Graph(nn)

for e in range(ne):
    edge = input().split(" ")
    u, v, w = int(edge[0]), int(edge[1]), float(edge[2])
    G.add_edge(u, v, w)

prim(G)
