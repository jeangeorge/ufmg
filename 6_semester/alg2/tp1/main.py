import sys
import os

from trie import Trie
from utils import *

def compress_file(input_file, output_file):
	# Tenta abrir arquivo e pegar o texto
	with open(input_file, "r") as file:
		text = file.read()

	# Instancia a trie inicial
	trie = Trie()

	compressed_text = trie.populate_and_compress(text)
	if output_file:
		file_name = output_file
	else:
		file_name = input_file.replace('.txt', '.z78')

	with open(file_name, 'wb') as file:
		encoded_compressed_text = compressed_text.encode('utf-8')
		file.write(encoded_compressed_text)

def decompress_file(input_file, output_file):
	trie = Trie()

# Funcao inicial do programa
# ./<programa> -c teste.txt >>>>> resulta em >>>>> teste.z78
def main(argv):
	# Tenta pegar os argumentos
	# Menos de tres argumentos indica o erro, nesse caso o programa deve ser encerrado
	if not is_valid_argv(argv):
		print("Invalid program arguments")
		sys.exit()

	# Se eh compressao ou descompressao: -c ou -x
	operation_type = argv[1]
	if not is_valid_operation_type(operation_type):
		print("Invalid operation type")
		sys.exit()

	# Arquivo de entrada: terminado em .txt .z78
	input_file = argv[2]
	if not is_valid_file(input_file):
		print("Invalid input file name")
		sys.exit()

	# Caso tenha quatro argumentos signica que foi definido o arquivo de saida
	output_file = None
	if len(argv) == 4:
		output_file = argv[3]
		if not is_valid_file(output_file):
			print("Invalid output file name")
			sys.exit()

	# Realiza a compressao / descompressao
	if operation_type == "-c":
		compress_file(input_file, output_file)
	else:
		decompress_file(input_file, output_file)

if __name__ == "__main__":
	main(sys.argv)