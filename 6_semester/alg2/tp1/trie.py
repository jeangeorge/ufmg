from node import Node

class Trie(object):
	def __init__(self):
		self.index = 0
		self.root = Node("")

	def insert(self, word):
		node = self.root
		for char in word:
			if char in node.children:
				node = node.children[char]
			else:
				new_node = Node(char)
				node.children[char] = new_node
				node = new_node
		self.index += 1
		node.index = self.index
		node.is_end = True

	def dfs(self, node, pre):
		if node.is_end:
			self.output.append((pre + node.char, node))
		for child in node.children.values():
			self.dfs(child, pre + node.char)

	def search(self, x):
		node = self.root
		for char in x:
			if char in node.children:
				node = node.children[char]
			else:
				return []
		self.output = []
		self.dfs(node, x[:-1])
		return self.output

	def populate_and_compress(self, text):
		print("INPUT:")
		print(text)
		compressed_data = ""
		word = ''
		i = 0
		for char in text:
			i += 1
			word += char
			if not word in dict(self.search(word)):
				self.insert(word)
				nodes = dict(self.search(word[:-1]))
				if word[:-1] in nodes:
					compressed_data += "{}".format(nodes[word[:-1]].index) + word[-1]
				else:
					compressed_data += "0" + word[-1]
				word = ''
			elif i == len(text):
				nodes = dict(self.search(word))
				if word in nodes:
					compressed_data += "{}".format(nodes[word].index) + word[-1]
				else:
					compressed_data += "0" + word[-1]
				word = ''
		print("COMPRESSED:")
		print(compressed_data)
		return compressed_data

	# def populate(self, text):
	# 	text = "A_ASA_DA_CASA"
	# 	compressed_data = []
	# 	dictionnary = ['']
	# 	word = ''
	# 	i = 0
	# 	for char in text:
	# 		i += 1
	# 		word += char
	# 		if not word in dictionnary:
	# 			dictionnary.append(word)
	# 			comp_data.append([dictionnary.index(word[:-1]), word[-1]])
	# 			word = ''
	# 		elif i == len(text):
	# 			comp_data.append([dictionnary.index(word), ''])
	# 			word = ''
	# 	print(dictionnary)
	# 	print(comp_data)
	# 	return comp_data