datatype area = RConst of real 
  | AQuadrado of area 
  | ACirculo of area
  | ARetangulo of area * area;

fun eval (RConst r) = r
  | eval (AQuadrado(e1)) = (eval e1) * (eval e1)
  | eval (ACirculo(e1)) = 3.14 * (eval e1) * (eval e1)
  | eval (ARetangulo(e1, e2)) = (eval e1) * (eval e2);