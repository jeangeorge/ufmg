datatype UnOp = Not;
datatype BinOp = Add | Sub | Mul | Gt | Eq | Or;
datatype Sexpr = IConst of int | Op1 of UnOp * Sexpr | Op2 of BinOp * Sexpr * Sexpr;

fun simplify (IConst i) = IConst i
  | simplify (Op1(Not op, e1));

val e = Op1(Not,IConst 5);
simplify e;