import sys
import glob, os
import filecmp

from trie import Trie
from utils import *
from datetime import datetime

NUMBER_SIZE = 3
ENCODING = "utf-8"

def compress_file(input_file, output_file=""):
	# Tenta abrir arquivo e pegar o texto
	with open(input_file, "r", encoding=ENCODING) as file:
		text = file.read()

	# Instancia a trie
	trie = Trie(NUMBER_SIZE, ENCODING)

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

def decompress_file(input_file, output_file=""):
	# Dicionario para armazenar as palavras
	words = {0: ""}

	# O texto descomprimido
	uncompressed_text = ""

	# Variavel tamanho auxiliar
	size = 1

	i = 0
	# Tenta abrir e ler o arquivo binario
	with open(input_file, mode="rb") as file:
		binary = file.read()

	# Percorre o arquivo binario
	while i < len(binary):
		# Pega o index (caractere numerico) do algoritmo, eh utilizado NUMBER_SIZE porque o inteiro foi armazenado com essa quantidade de bytes
		index = int.from_bytes(binary[i : i + NUMBER_SIZE], byteorder="big")
		# Como nao sabemos exatamente o tamanho do caractere (pode ser 1, 2, 3 ou 4 bytes) fazemos o tratamento abaixo para pegar o valor correto
		value_byte = binary[i + NUMBER_SIZE : i + NUMBER_SIZE + 4]
		string_binary = "{0:b}".format(value_byte[0]).zfill(8)
		byte_interval = 1
		if string_binary.startswith("110"):
			byte_interval = 2
		elif string_binary.startswith("1110"):
			byte_interval = 3
		elif string_binary.startswith("11110"):
			byte_interval = 4
		# Para 1 byte, convertemos com conversao simples e para mais bytes fazemos o decode
		if byte_interval == 1:
			value = chr(binary[i + NUMBER_SIZE])
		else:
			value = value_byte[0:byte_interval].decode(ENCODING)
		# Atualizamos o dict e o texto descomprimido
		string = words[index] + value
		words[size] = string
		uncompressed_text += string
		size += 1
		# Andamos com o i a quantidade necessaria
		i += NUMBER_SIZE + byte_interval

	# Define o nome do arquivo de saida
	if output_file:
		file_name = output_file
	else:
		file_name = input_file.replace(".z78", ".txt")

	if uncompressed_text[-1] == "ぁ":
		uncompressed_text = uncompressed_text[:-1]

	# Tenta escrever no arquivo
	with open(file_name, mode="w") as file:
		file.write(uncompressed_text)

# Funcao que testa todos os arquivos .txt presentes na pasta tests
# Isto eh, comprime eles, descomprime e
def test(file_name):
	os.makedirs("./tests/results", exist_ok=True)
	os.chdir("./tests")
	text = ""
	print("init tests")
	for input_file in glob.glob("*.txt"):
		if input_file == file_name:
			continue
		print("working with " + input_file + "...")
		output_file = "./results/" + input_file.replace(".txt", "-output.z78")
		compress_file(input_file, output_file)
		decompress_file(output_file)
		original_size = os.path.getsize("./" + input_file)
		compressed_size = os.path.getsize(output_file)
		ratio = original_size / compressed_size
		if filecmp.cmp(output_file.replace(".z78",".txt"), input_file):
			equal = "yes"
		else:
			equal = "no"
		text += input_file + " - comp ratio: " + "{}".format(ratio) + " - equal: " + equal + "\n"
	print("tests saved!")
	with open("./results/" + file_name, mode="w") as file:
		file.write(text)

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
	elif operation_type == "-x":
		decompress_file(input_file, output_file)
	else:
		test(input_file)


if __name__ == "__main__":
	main(sys.argv)