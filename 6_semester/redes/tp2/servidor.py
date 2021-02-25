import socket
import os
import sys
import struct
import select

from threading import Thread

from constants import *

def get_free_udp_port():
	udp = socket.socket(socket.AF_INET6, socket.SOCK_DGRAM)
	udp.bind(('', 0))
	udp.setsockopt(socket.SOL_SOCKET, socket.SO_REUSEADDR, 1)
	port = udp.getsockname()[1]
	udp.close()
	return port

files = {}
udp_port = get_free_udp_port()

# Thread para receber dados dos clientes
def tcp_thread(connection):
	while True:
		# Recebe os dados em bytes
		data = connection.recv(MAX_SIZE)
		if not data:
			break
		reply = ""
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
			file_name = data[2:17].decode(ENCODING).replace('\0','')
			file_size = struct.unpack(">q", data[17:])[0]
			files[connection.getpeername()] = (file_name, file_size)
			bytes_type = struct.pack(">h", OK)
			reply = bytes_type
			print("INFO FILE recebido, enviando OK para o cliente")
		elif message_type == FIM:
			print("FIM recebido, encerrando conexão TCP")
			break
		connection.sendall(reply)
	connection.close()

def udp_thread(udp_socket, tcp_adress):
	file_name = files[tcp_adress][0]
	file_size = files[tcp_adress][1]
	os.chdir(".")
	if os.path.isdir("saida") == False:
		os.mkdir("saida")
	f = open("./saida/" + file_name, 'wb')
	next_sequence_number = 0
	print("Iniciando o recebimento do arquivo...")
	while True:
		ready = select.select([udp_socket], [], [], 0.1)
		if ready[0]:
			data, udp_address = udp_socket.recvfrom(MAX_SIZE)
			message_type = struct.unpack(">h", data[:2])[0]
			sequence_number = struct.unpack(">i", data[2:6])[0]
			payload_size = struct.unpack(">h", data[6:8])[0]
			payload_file = data[8:]
			f.write(payload_file)
			bytes_type = struct.pack(">h", ACK)
			bytes_sequence_number = struct.pack(">i", sequence_number)
			udp_socket.sendto(bytes_type + bytes_sequence_number, udp_address)
		else:
			print ("Arquivo completamento recebido!")
			f.close()
			break

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

	# Cria um socket TCP e define que o endereço pode ser reutilizado
	tcp_socket = socket.socket(socket.AF_INET6, socket.SOCK_STREAM)
	tcp_socket.setsockopt(socket.SOL_SOCKET, socket.SO_REUSEADDR, 1)
	try:
		tcp_socket.setsockopt(socket.IPPROTO_IPV6, socket.IPV6_V6ONLY, 0)
	except (AttributeError, socket.error):
		pass

	# Cria um socket UDP
	udp_socket = socket.socket(socket.AF_INET6, socket.SOCK_DGRAM)
	udp_socket.setsockopt(socket.SOL_SOCKET, socket.SO_REUSEADDR, 1)
	try:
		udp_socket.setsockopt(socket.IPPROTO_IPV6, socket.IPV6_V6ONLY, 0)
	except (AttributeError, socket.error):
		pass

	# Tenta dar o bind em todos os endereços
	try:
		tcp_socket.bind(("::", port))
	except socket.error as e:
		print(str(e))
	try:
		udp_socket.bind(("::", udp_port))
	except socket.error as e:
		print(str(e))

	# Define o backlog
	tcp_socket.listen(5)
	print("Servidor rodando, aguardando conexões...")


	while True:
		tcp_client, tcp_adress = tcp_socket.accept()
		print("Conexão TCP recebida de: " + tcp_adress[0] + ":" + str(tcp_adress[1]))
		# start_new_thread(tcp_thread, (tcp_client,))
		t1 = Thread(target=tcp_thread, args=(tcp_client,))
		t1.start()
		t1.join()
		t2 = Thread(target=udp_thread, args=(udp_socket, tcp_adress))
		t2.start()
		t2.join()
	udp_socket.close()
	tcp_socket.close()


if __name__ == "__main__":
	main(sys.argv)
