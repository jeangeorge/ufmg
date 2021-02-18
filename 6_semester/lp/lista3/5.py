NULL = -1

class HeapManager:
	def __init__(self, initialMemory):
		self.memory = initialMemory
		self.memory[0] = self.memory.__len__()
		self.memory[1] = NULL
		self.freeStart = 0

	def allocate(self, requestSize):
		size = requestSize + 1
		p = self.freeStart
		lag = NULL
		while p != NULL and self.memory[p] < size:
			lag = p
			p = self.memory[p + 1]
		if p == NULL:
			raise MemoryError()
		nextFree = self.memory[p + 1]
		unused = self.memory[p] - size
		if unused > 1:
			nextFree = p + size
			self.memory[nextFree] = unused
			self.memory[nextFree + 1] = self.memory[p + 1]
			self.memory[p] = size
		if lag == NULL:
			self.freeStart = nextFree
		else:
			self.memory[lag + 1] = nextFree
		return p + 1

	def deallocate(self, address):
		addr = address - 1
		self.memory[addr + 1] = self.freeStart
		self.freeStart = addr

def test () :
	h = HeapManager([0 for x in range (0 , 10) ])
	a = h.allocate (4)
	print("a = ", a, ", Memory = ", h.memory)
	b = h.allocate (2)
	print("b = ", b, ", Memory = ", h.memory )

test()