signature MYMATH =
sig
    val halfPi : real
    val fact : int -> int
    val pow : int * int -> int
    val double : int -> int
end;

structure MyMathLib :> MYMATH =
struct
    val halfPi = Math.pi / 2.0
    fun fact n = if n = 0 then 1 else n * fact(n - 1)
    fun pow (n, c) = if c = 0 then 1 else n * pow(n, c-1)
    fun double n = n * 2
end;