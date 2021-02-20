class FilePacket:
    def __init__(self, message_type, sequence_number, payload_size, payload_file):
        self.message_type = message_type
        self.sequence_number = sequence_number
        self.payload_size = payload_size
        self.payload_file = payload_file

    def to_bytes(self):
        return self.message_type + self.sequence_number + self.payload_size +  self.payload_file