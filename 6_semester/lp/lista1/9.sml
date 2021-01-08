datatype dinheiro = Real of real | Centavos of int | Pessoa_Dinheiro of string*real;

fun amount (Real x) = floor(x*100.0)
	| amount(Centavos x) = x
	| amount(Pessoa_Dinheiro (_, x)) = floor(x*100.0);