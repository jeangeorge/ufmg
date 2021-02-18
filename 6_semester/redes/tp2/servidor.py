import socket
import os
import sys
import struct

from _thread import *

from constants import *

def get_free_udp_port():
	udp = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)
	udp.bind(('', 0))
	udp.setsockopt(socket.SOL_SOCKET, socket.SO_REUSEADDR, 1)
	port = udp.getsockname()[1]
	udp.close()
	return port

# Thread para receber dados dos clientes
def threaded_client(connection):
	while True:
		# Recebe os dados em bytes
		data = connection.recv(MAX_SIZE)
		if not data:
			break
		reply = ""
		# Gera uma porta IPv4 UDP
		udp_port = get_free_udp_port()
		# Avalia os dois primeiros bytes da mensagem
		message_type = struct.unpack(">h", data[:2])[0]
		if message_type == HELLO:
			# Caso tenha recebido um HELLO:
			# retorna a mensgem CONNECTION para o cliente, informando a porta UDP
			bytes_type = struct.pack(">h", CONNECTION)
			bytes_port = struct.pack(">i", udp_port)
			reply = bytes_type + bytes_port
			print("HELLO recebido, enviando CONNECTION para o cliente")
		elif message_type == INFO_FILE:
			# Caso tenhamos recebido um INFO_FILE:
			# Alocamos o que precisa para a janela deslizante
			# WIP
			bytes_type = struct.pack(">h", OK)
			reply = bytes_type
			print("INFO FILE recebido, enviando OK para o cliente")
		elif message_type == FIM:
			print("FIM recebido, encerrando conexão TCP")
			break
		connection.sendall(reply)
	connection.close()


def usage(argv):
	print("usage: " + argv[0] + " <server port>")
	print("example: " + argv[0] + " 51511")
	sys.exit()


# # Funcao inicial do servidor
def main(argv):
	# Valida os argumentos
	if len(argv) < 2:
		usage(argv)

	port = int(argv[1])
	if not port:
		sys.exit()

	# Cria um socket e define que o endereço pode ser reutilizado
	tcp_socket = socket.socket()
	tcp_socket.setsockopt(socket.SOL_SOCKET, socket.SO_REUSEADDR, 1)

	# Tenta dar o bind em todos os endereços
	try:
		tcp_socket.bind(("{}".format(socket.INADDR_ANY), port))
	except socket.error as e:
		print(str(e))

	# Define o backlog
	tcp_socket.listen(5)
	print("Servidor rodando, aguardando conexões...")

	thread_count = 0

	while True:
		client, address = tcp_socket.accept()
		print("Conexão recebida de: " + address[0] + ":" + str(address[1]))
		start_new_thread(threaded_client, (client,))
		thread_count += 1
	tcp_socket.close()


if __name__ == "__main__":
	main(sys.argv)
