fun pow(n: int, c: int)
	= if c = 0
		then 1
	else
		n * pow (n, c-1);