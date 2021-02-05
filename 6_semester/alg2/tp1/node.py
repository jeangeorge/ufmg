class Node:
	def __init__(self, char, index=0):
		self.char = char
		self.index = index
		self.is_end = False
		self.children = {}