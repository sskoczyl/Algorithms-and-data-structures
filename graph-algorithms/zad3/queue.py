import math


class Queue:
    def __init__(self):
        self.heap_list = []
        self.queue_size = 0

    def heapify(self, xl):
        min_idx, l, r = xl, 2 * xl + 1, 2 * xl + 2

        if l < self.queue_size and self.heap_list[l][1] < self.heap_list[min_idx][1]:
            min_idx = l
        if r < self.queue_size and self.heap_list[r][1] < self.heap_list[min_idx][1]:
            min_idx = r

        if min_idx != xl:
            self.swp(min_idx, xl)
            self.heapify(min_idx)

    def swp(self, u, v):
        self.heap_list[u], self.heap_list[v] = self.heap_list[v], self.heap_list[u]

    def decrease_key(self, e, np):
        i = self.heap_list.index(e)
        self.heap_list[i] = tuple([e[0], np])
        t = self.heap_list[i]

        while i > 0:
            parent_idx = math.floor((i - 1) / 2)
            if not self.heap_list[parent_idx][1] > t[1]:
                break

            self.heap_list[i] = self.heap_list[parent_idx]
            i = parent_idx
        self.heap_list[i] = t

    def is_empty(self):
        return not bool(self.queue_size)

    def insert(self, el, p):
        inserted, i = tuple([el, p]), self.queue_size
        self.heap_list.append(inserted)
        self.queue_size += 1

        while i > 0:
            prnt_id = math.floor((i - 1) / 2)

            if not self.heap_list[prnt_id][1] > p:
                break

            self.heap_list[i], i = self.heap_list[prnt_id], prnt_id

        self.heap_list[i] = inserted

    def pop(self):
        if self.queue_size == 0:
            return None
        else:
            min_el, self.heap_list[0] = self.heap_list[0], self.heap_list[self.queue_size-1]
            self.queue_size -= 1
            del (self.heap_list[self.queue_size])
            self.heapify(0)
            return min_el

    def min(self):
        return self.heap_list[0] if not self.is_empty() else "\n"

    def priority(self, w, np):
        for e in self.heap_list:
            if e[0] == w and e[1] > np:
                self.decrease_key(e, np)

    def check_if_in_heap(self, v):
        for e in self.heap_list:
            if e[0] == v:
                return True
        else:
            return False
