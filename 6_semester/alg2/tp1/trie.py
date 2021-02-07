# -*- coding: utf-8 -*-

import sys

from node import Node
from utils import *

class Trie(object):
	def __init__(self, byte_size, encoding):
		self.index = 0
		self.root = Node("")
		self.compressed_text = bytearray(0)
		self.byte_size = byte_size
		self.encoding = encoding

	# Inserindo uma palavra na trie
	def insert(self, word):
		node = self.root
		# Primeiro tenta achar o ultimo no da palavra na trie, caso ele exista
		# Se nao existir cria um
		for char in word:
			if char in node.children:
				node = node.children[char]
			else:
				new_node = Node(char)
				node.children[char] = new_node
				node = new_node
		# Incrementa em um para ter comportamento igual a um dic normal
		self.index += 1
		node.index = self.index
		# Define que eh o fim de uma palavra
		node.is_end = True

	# Buscando uma palavra na trie
	def search(self, word):
		current_node = self.root
		# Percorre a palavra caractere a caractere
		for char in word:
			# Se o caractere nao eh indice de nenhum no filho eh porque nao esta na trie
			if char not in current_node.children:
				return False, 0
			# Se eh, continua buscando
			current_node = current_node.children[char]
		# Caso indique o fim de uma palavra, retornamos que a palavra esta na trie e tambem o index
		if current_node.is_end:
			return True, current_node.index
		else:
			return False, 0

	# Inserindo os dados na trie e atualizando o texto comprimido
	def populate_and_compress(self, text):
		word = ''
		i = 0
		# Percorre o texto caractere a caractere
		for char in text:
			i += 1
			word += char
			word_substring = word[:-1]
			# Busca a palavra atual e palavra atual sem o ultimo caractere na trie
			find_word, index_word = self.search(word)
			find_word_substring, index_word_substring = self.search(word_substring)
			if not find_word:
				# Se nao encontrar a palavra eh preciso inserir na trie
				self.insert(word)
				# E tambem setar o correto na compressao
				self.set_compressed_text(index_word_substring, word[-1])
				word = ''
			elif i == len(text):
				# Se encontrar a palavra e estivermos no fim do arquivo, adicionamos um caractere especial
				# Isso foi necessario para nao bugar na descompressao
				self.set_compressed_text(index_word, 'ぁ')
				word = ''
		return self.compressed_text

	# Recebe um index e o texto e concatena no array de bytes resultante
	def set_compressed_text(self, index, text):
		index_bytes = index.to_bytes(length=self.byte_size, byteorder='big')
		text_bytes = text.encode(self.encoding)
		self.compressed_text = b"".join([self.compressed_text, index_bytes, text_bytes])