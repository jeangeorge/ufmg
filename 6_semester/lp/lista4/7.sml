signature MYMATH =
sig
    exception NegativeException
    val halfPi : real
    val fact : int -> int
    val pow : int * int -> int
    val double : int -> int
end;

structure MyMathLib :> MYMATH =
struct
    exception NegativeException
    val halfPi = Math.pi / 2.0
    fun fact n = if n > 0 then n * fact(n - 1) else raise NegativeException
    fun pow (0, 0) = 1
        | pow (n, 0) =  if n > 0 then 1 else raise NegativeException
        | pow (n, c) = if n > 0 then n * pow(n, c-1) else raise NegativeException
    fun double n = if n > 0 then n * 2 else raise NegativeException
end;

fun useMyMathLibAux (x, "pow") = print(Int.toString(MyMathLib.pow(x,x)))
    | useMyMathLibAux (x, "double") = print(Int.toString(MyMathLib.double(x)))
    | useMyMathLibAux (x, "fact") = print(Int.toString(MyMathLib.fact(x)))
    | useMyMathLibAux (x, _) = raise Match;

fun useMyMathLib(x, y) = useMyMathLibAux(x, y) handle NegativeException => (print("Não posso lidar com valores negativos!"));