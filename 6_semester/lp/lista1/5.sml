fun cumSum([]) = []
	| cumSum(x::[]) = x::[]
	| cumSum(x::y::z) = x::cumSum((x+y)::z);