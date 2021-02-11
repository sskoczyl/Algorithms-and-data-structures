from collections import defaultdict
import sys


class Graph:
    def __init__(self, v):
        self.verticles, self.graph = v, []

    def add_edge(self, u, v, w):
        self.graph.append([u, v, w])
        self.graph.append([v, u, w])

    def union(self, p, rnk, x, y):
        xr, yr = self.check_if_in(p, x), self.check_if_in(p, y)

        if rnk[xr] < rnk[yr]:
            p[xr] = yr

        elif rnk[xr] > rnk[yr]:
            p[yr] = xr

        else:
            p[yr] = xr
            rnk[xr] += 1

    def kruskal(self):
        out, p, rnk = [], [], []
        i, e = 0, 0
        graph = sorted(self.graph, key=lambda item: item[2])

        for node in range(self.verticles):
            p.append(node)
            rnk.append(0)

        while e < self.verticles - 1:

            u, v, w = graph[i]
            i = i + 1
            x = self.check_if_in(p, u)
            y = self.check_if_in(p, v)
            if x != y:
                e = e + 1
                out.append([u, v, w])
                self.union(p, rnk, x, y)
        ws = 0

        for u, v, w in out:
            ws += w
            print(u, v, w)

        print(ws)

    def check_if_in(self, p, i):
        if p[i] == i:
            return i
        return self.check_if_in(p, p[i])


nn = int(input())
ne = int(input())
G = Graph(nn)

for e in range(ne):
    edge = input().split(" ")
    u, v, w = int(edge[0]), int(edge[1]), float(edge[2])
    G.add_edge(u, v, w)

G.kruskal()
