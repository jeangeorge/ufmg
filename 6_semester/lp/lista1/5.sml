fun invert([]) = [] | invert(h::t) = invert(t) @ [h];

fun sum([]) = 0 | sum(h::t) = h + sum(t);

fun cumSum([]) = [] |
	cumSum(x) =  cumSum(tl(invert(x))) @ [sum(invert(tl(x))) + hd(x)];

(* invert([6,10,3,11]);
sum([6,10,3,11]); *)
cumSum([6,10,3,11]);
(* // FALTANDO *)