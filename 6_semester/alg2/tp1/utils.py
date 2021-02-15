def is_valid_argv(argv):
	return len(argv) >= 3

def is_valid_operation_type(operation_type):
	return operation_type == "-c" or operation_type == "-x" or operation_type == "-t"

def is_valid_file(file):
	if not file:
		return False
	file_extension = file.split(".")[1]
	return file_extension == "z78" or file_extension == "txt"

def is_ascii(s):
	return all(ord(c) < 128 for c in s)