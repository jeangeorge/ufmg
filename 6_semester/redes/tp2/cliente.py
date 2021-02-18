import sys
import os
import socket
import struct
import time

from constants import *

def teste():
	ClientSocket = socket.socket()
	host = "127.0.0.1"
	port = 1233

	print("Waiting for connection")
	try:
		ClientSocket.connect((host, port))
	except socket.error as e:
		print(str(e))

	Response = ClientSocket.recv(MAX_SIZE)
	while True:
		Input = input("Say Something: ")
		ClientSocket.send(str.encode(Input))
		Response = ClientSocket.recv(MAX_SIZE)
		print(Response.decode("utf-8"))

	ClientSocket.close()


def usage(argv):
	print("usage: " + argv[0] + " <server IP> <server port> <file name>")
	print("example: " + argv[0] + " 127.0.0.1 51511 file.doc")
	sys.exit()


def is_ascii(string):
	return all(ord(char) < 128 for char in string)


def is_valid_file_name(file_name):
	if not file_name:
		return False
	# Validando se o a string tem menos de 15 bytes
	if len(file_name.encode("ascii")) > 15:
		return False
	if is_ascii(file_name) == False:
		return False
	# Validando se tem apenas um ponto "."
	if not (file_name.count(".") == 1):
		return False
	if not (len(file_name.split(".")[1]) == 3):
		return False
	return True


# Funcao inicial do cliente
def main(argv):
	# Valida os argumentos
	if len(argv) < 4:
		usage(argv)

	# Valida o nome do arquivo
	file_name = argv[3]
	if not is_valid_file_name(file_name):
		print("Nome não permitido")
		sys.exit()

	# Verifica se o arquivo existe
	if os.path.exists(file_name) == False:
		print("Arquivo inexistente")
		sys.exit()

	# Valida o endereco do host e a porta
	host = argv[1]
	port = int(argv[2])
	if not host or not port:
		sys.exit()

	address_family = socket.getaddrinfo(host, port)[0][0]

	# Cria um socket
	tcp_socket = socket.socket(address_family, socket.SOCK_STREAM)

	# Tenta fazer a conexao
	try:
		tcp_socket.connect((host, port))
		print("Conexão via TCP realizada com sucesso com o servidor", host)
	except socket.error as e:
		print("Erro ao realizar a conexão TCP com o servidor")
		print(str(e))
		sys.exit()

	# Nesse ponto ja esta conectado
	# Envia a primeira mensagem de HELLO
	hello_message = struct.pack(">h", HELLO)
	tcp_socket.send(hello_message)

	# Recebe a resposta do HELLO do servidor
	response = tcp_socket.recv(MAX_SIZE)

	# Pega o tipo da mensagem
	message_type = struct.unpack(">h", response[:2])[0]
	# Como enviamos um HELLO esperamos receber um CONNECTION
	if (message_type == CONNECTION):
		# Pega a porta UDP
		udp_port = struct.unpack(">i", response[2:])[0]
		# Precisamos agora enviar uma mensagem de INFO_FILE para o servidor
		# Montamos o cabeçalho
		message_type_bytes = struct.pack(">h", INFO_FILE)
		zero_bytes = bytes(15 - len(file_name))
		file_name_bytes = file_name.encode(ENCODING)
		file_size_bytes = struct.pack(">q", os.stat(file_name).st_size)
		message_info_file = message_type_bytes + zero_bytes + file_name_bytes + file_size_bytes
		# Enviamos
		tcp_socket.send(message_info_file)
		# Obtemos a resposta
		response = tcp_socket.recv(MAX_SIZE)
		message_type = struct.unpack(">h", response)
		# Como enviamos um INFO_FILE esperamos receber um OK
		if (message_type == OK):
			# Precisamos agora enviar um FIM para o cliente
			message_type_bytes = struct.pack(">h", FIM)
			tcp_socket.send(message_type_bytes)
			# Agora começaremos a transmitir o arquivo
			# Cria o socket udp
			# udp_socket = socket.socket(address_family, socket.SOCK_DGRAM)
			# udp_socket.sendto(file_name, (host, udp_port))
			# print ("Enviando %s ..." % file_name)
			# # Abre o arquivo e le os 1000 primeiros bytes
			# file = open(file_name, "r")
			# data = file.read(1000)
			# sequence_number = 0
			# while(data):
    		# 	# Monta a mensagem FILE para enviar
			# 	message_type_bytes = struct.pack(">h", FILE)
			# 	message_type_bytes = struct.pack(">", FILE)
    		# 	if udp_socket.sendto(data, (host, udp_port)):
			# 		data = file.read(1000)
			# 		time.sleep(0.02)
			# udp_socket.close()
			# file.close()
		else:
    		print("Ocorreu um erro no envio do INFO FILE")
	else:
		print("Ocorreu um erro no no envio do HELLO")
	# Fecha a conexao
	tcp_socket.close()


if __name__ == "__main__":
	main(sys.argv)
