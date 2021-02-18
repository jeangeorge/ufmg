from constants import *

def stringToHex(string):
    return string.encode(ENCODING).hex()

def stringToBytes(string):
    return bytes(bytearray.fromhex(stringToHex(string)))

def bytesToString(bytes):
    return ''.join(format(x, '02x') for x in bytearray(bytes))