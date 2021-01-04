fun sumLists(m, []) = m
	| sumLists([], n) = n
	| sumLists(x::m, y::n) = (x+y)::sumLists(m,n);