from queue import Queue
class Item:
       def __init__(self, value, weight):
        self.value = value
        self.weight = weight

class Node:
    def __init__(self):
        self.level = -1
        self.profit = 0
        self.bound = 0
        self.weight = 0

class Knapsack:
    def __init__(self):
        self.items = []
        self.max_items = 0
        self.max_weight = 0
        self.solution_backtracking = 0
        self.solution_branch_and_bound = 0

    def solve_backtracking(self, index, weight, value):
        if (index == self.max_items):
            if weight <= self.max_weight:
                if self.solution_backtracking <= value:
                    self.solution_backtracking = value
            return
        self.solve_backtracking(index + 1, weight + self.items[index].weight, value + self.items[index].value)
        self.solve_backtracking(index + 1, weight, value)

    def solve_branch_and_bound(self):
        queue = Queue()
        u = Node()
        v = Node()
        self.items = sorted(self.items, key=lambda x: x.value/x.weight, reverse=True)
        queue.put(u)
        max_profit = 0;
        while not queue.empty():
            u = queue.get()
            v = Node()
            if u.level == -1:
                v.level = 0
            if u.level == self.max_items - 1:
                continue
            v.level = u.level + 1
            v.weight = u.weight + self.items[v.level].weight
            v.profit = u.profit + self.items[v.level].value
            if (v.weight <= self.max_weight and v.profit > max_profit):
                max_profit = v.profit;
            v.bound = self.bound(v)
            if (v.bound > max_profit):
                queue.put(v)
            v = Node()
            v.level = u.level + 1
            v.weight = u.weight
            v.profit = u.profit
            v.bound = self.bound(v)
            if (v.bound > max_profit):
                queue.put(v)
        self.solution_branch_and_bound = max_profit

    def bound(self, node):
        if(node.weight >= self.max_weight):
            return 0
        profit_bound = node.profit
        j = node.level + 1
        to_weight = node.weight
        while j < self.max_items and to_weight + self.items[j].weight <= self.max_weight:
            to_weight += self.items[j].weight
            profit_bound += self.items[j].value
            j += 1
        if j < self.max_items:
            profit_bound += (self.max_weight - to_weight) * self.items[j].value / self.items[j].weight
        return profit_bound