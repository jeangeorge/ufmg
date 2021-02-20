import sys
import os
import socket
import struct
import time

from file_packet import FilePacket

from constants import *

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

# Recebe o arquivo em bytes e retorna um array no formato FILE
def create_file_packets(file):
	packets = []
	message_type = struct.pack(">h", FILE)
	sequence_number = 0
	data = file.read(1000)
	packets.append(FilePacket(message_type, struct.pack(">i", sequence_number), struct.pack(">h", len(data)), data.encode(ENCODING)))
	while data:
		sequence_number += 1
		data = file.read(1000)
		if data:
			packets.append(FilePacket(message_type, struct.pack(">i", sequence_number), struct.pack(">h", len(data)), data.encode(ENCODING)))
	return packets

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
		print("Conexão realizada com sucesso com o servidor", host)
	except socket.error as e:
		print("Erro ao realizar a conexão TCP com o servidor")
		print(str(e))
		sys.exit()

	# Nesse ponto ja esta conectado via TCP
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
		message_type = struct.unpack(">h", response)[0]
		# Como enviamos um INFO_FILE esperamos receber um OK
		if (message_type == OK):
			# Precisamos agora enviar um FIM para o cliente
			message_type_bytes = struct.pack(">h", FIM)
			tcp_socket.send(message_type_bytes)
			# Agora começaremos a transmitir o arquivo
			# Cria o socket udp
			udp_socket = socket.socket(address_family, socket.SOCK_DGRAM)
			# Abre o arquivo e le os 1000 primeiros bytes
			file = open(file_name, "rb")
			data = file.read(1000)
			sequence_number = 0
			print ("Enviando %s ..." % file_name)
			while(data):
				# Monta a mensagem FILE para enviar
				message_type_bytes = struct.pack(">h", FILE)
				sequence_number_bytes = struct.pack(">i", sequence_number)
				payload_size_bytes = struct.pack(">h", len(data))
				message_file = message_type_bytes + sequence_number_bytes + payload_size_bytes + data
				# Tenta enviar e continua a leitura
				if udp_socket.sendto(message_file, (host, udp_port)):
					response = udp_socket.recv(MAX_SIZE)
					message_type_received = struct.unpack(">h", response[:2])[0]
					sequence_number_received = struct.unpack(">i", response[2:])[0]
					if message_type_received == ACK and sequence_number_received == sequence_number:
						sequence_number += 1
						data = file.read(1000)
					time.sleep(0.001)
			print("Arquivo enviado!")
			udp_socket.close()
			file.close()
		else:
			print("Ocorreu um erro no envio do INFO FILE")
	else:
		print("Ocorreu um erro no no envio do HELLO")
	# Fecha a conexao
	tcp_socket.close()


if __name__ == "__main__":
	main(sys.argv)
