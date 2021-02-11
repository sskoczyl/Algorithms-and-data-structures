from timeit import default_timer as timer
from collections import defaultdict
from random import choice
from operator import itemgetter
import sys


class Graph:
    def __init__(self, v):
        self.vertices, self.G = v, defaultdict(list)

    def add_edge(self, s, d, w):
        self.G[s].insert(0, [d, w])
        self.G[d].insert(0, [s, w])

    def random_traversal(self):
        distance, s = 0, 0
        visited, vertex = set(), choice(list(self.G.keys()))
        visited.add(next)

        while len(visited) < self.vertices:
            vertex = choice(self.G[vertex])[0]
            distance += choice(self.G[vertex])[1]
            print(vertex, distance, file=sys.stderr)
            visited.add(vertex)

            s += 1
        print(s, distance, sys.getsizeof(visited), end=' ')

    def greedy_traversal(self):
        distance, s = 0, 0
        visited, vertex = set(), choice(list(self.G.keys()))
        visited.add(next)

        while len(visited) < self.vertices:
            for vrtx in sorted(self.G[vertex], key=itemgetter(1)):
                if vrtx[0] not in visited:
                    print(vrtx[0], vrtx[1], file=sys.stderr)
                    vertex = vrtx[0]
                    distance += vrtx[1]
                    break

                s += 1

            visited.add(vertex)

        print(s, distance, sys.getsizeof(visited), end=' ')


nodes = int(input())
edges = int(input())
graph = Graph(nodes)

for e in range(edges):
    edge = input().split(" ")
    u, v, weight = int(edge[0]), int(edge[1]), float(edge[2])
    graph.add_edge(u, v, weight)

start_time = timer()
time = 0
graph.random_traversal()
time = timer()
time -= start_time
print(time)

start_time = timer()
time = 0
graph.greedy_traversal()
time = timer()
time -= start_time
print(time)
