fun max([]) = 0 | max(x::y) =
	if x > max(y)
		then x
	else max(y);