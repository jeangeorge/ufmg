import sys

from trie import Trie
from utils import *
from datetime import datetime

BYTE_SIZE = 3
ENCODING = "utf-8"

def compress_file(input_file, output_file):
	# Tenta abrir arquivo e pegar o texto
	with open(input_file, "r") as file:
		text = file.read()

	# Instancia a trie
	trie = Trie(BYTE_SIZE, ENCODING)

	# Popula a trie com o texto e obtem o texto compactado
	compressed_text = trie.populate_and_compress(text)

	# Pega o nome do arquivo
	if output_file:
		file_name = output_file
	else:
		file_name = input_file.replace(".txt", ".z78")

	# Escreve o binario do arquivo comprimido
	with open(file_name, "wb") as file:
		file.write(compressed_text)

def decompress_file(input_file, output_file):
	# Dicionario para armazenar as palavras
	words = {0: ""}

	# O texto descomprimido
	uncompressed_text = ""

	# Variavel tamanho auxiliar
	size = 1

	# Tenta abrir e ler o arquivo binario
	with open(input_file, mode="rb") as file:
		binary = file.read()

	# Percorre o arquivo binario, caractere a caractere andando em passo BYTE_sIZE + 1
	for i in range(0, len(binary), BYTE_SIZE + 1):
		if (i + BYTE_SIZE >= len(binary)):
			continue
		# Pega o "index na trie"
		index = int.from_bytes(binary[i : i + BYTE_SIZE], byteorder="big")
		# Pega a palavra
		value = chr(binary[i + BYTE_SIZE])
		string = words[index] + value
		words[size] = string
		uncompressed_text += string
		size += 1

	# Define o nome do arquivo de saida
	if output_file:
		file_name = output_file
	else:
		file_name = input_file.replace(".z78", ".txt")

	# Tenta escrever no arquivo
	with open(file_name, mode="w") as file:
		file.write(uncompressed_text)

# Funcao inicial do programa
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