class Node:
    def __init__(self):
        self.n = 0
        self.e = ''

class Stack:
    def __init__(self):
        self.root = 0
    
    def add(self, value):
        node = Node()
        node.e  = value
        if self.root != 0:
            node.n = self.root
        self.root = node
        
    def remove(self):
        node = self.root
        self.root = node.n
        return node.e
    
    def isNotEmpty(self):
        return self.root != 0