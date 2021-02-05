def is_valid_argv(argv):
	return len(argv) >= 3

def is_valid_operation_type(operation_type):
	return operation_type == "-c" or operation_type == "-x"

def is_valid_file(file):
	file_extension = file.split(".")[1]
	return file_extension == "z78" or file_extension == "txt"