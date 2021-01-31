datatype UnOp = Not;
datatype BinOp = Add | Sub | Mul | Gt | Eq | Or;
datatype Sexpr = IConst of int | Op1 of UnOp * Sexpr | Op2 of BinOp * Sexpr * Sexpr;

fun eval (IConst i) = i
	| eval (_) = ~1;

fun simplify (e) =
		case e of
			IConst e => IConst e
		| Op1(_, e) => IConst(~ (eval e))
		| Op2(binop, e1, e2) =>
			let
				val value1 = simplify e1;
				val value2 = simplify e2;
			in
				case binop of
					Add =>
						if (eval value1) = 0 then
							value2
						else
							if (eval value2) = 0 then
								value1
							else
								Op2(binop, e1, e2)
					| Sub =>
						if eval e2 = 0 then
							value1
						else
							if eval value1 = eval value2 then
								simplify(IConst 0)
							else
								Op2(binop, e1, e2)
					| Mul =>
						if eval value1 = 1 then
							value2
						else
							if eval value2 = 1 then
								value1
							else
								if eval value1 = 0 then
									simplify (IConst 0)
								else
									if eval value2 = 0 then
										value1
									else
										Op2(binop, e1, e2)
					| Gt => Op2(binop, e1, e2)
					| Eq => Op2(binop, e1, e2)
					| Or =>
						if  value1 =  value2 then
							value1
						else
							Op2(binop, e1, e2)
			end
;

val b = Op2(Mul, Op2(Add, IConst 1, IConst 0), Op2(Add, IConst 9, IConst 0));
simplify b;

val b2 = Op2 (Mul, Op2 (Add, IConst 1, IConst 0), Op2 (Add, Op2 (Or, IConst 10,
				IConst 12), IConst 0));
simplify b2;