class Node:
	def __init__(self):
		self.n = 0
		self.e = ''

class Queue:
	def __init__(self):
		self.start = 0
		self.end = 0
	
	def add(self, value):
		node = Node()
		node.e = value
		if self.start == 0:
			self.start = node
		else:
			self.end.n = node
		self.end = node

	def remove(self):
		if self.start == self.end:
			self.end = 0
		node = self.start
		self.start = node.n
		return node.e

	def isNotEmpty(self):
		return self.start != 0

	def getSmaller(self):
		if self.start != 0:
			smaller = self.start.e
		else:
			smaller = ''
		if self.start.n != 0:
			node = self.start.n
		else:
			node = 0
		while node:
			if node.e < smaller:
				smaller = node.e
			node = node.n
		return smaller