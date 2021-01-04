fun allTrue([]) = true
	| allTrue(x::y) =
		x = true andalso allTrue(y);