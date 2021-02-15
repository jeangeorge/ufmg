datatype perimetro = RConst of real 
  | PQuadrado of perimetro 
  | PCirculo of perimetro
  | PRetangulo of perimetro * perimetro
  | PTriangulo of perimetro * perimetro * perimetro;

fun eval (RConst r) = r
  | eval (PQuadrado(e1)) = (eval e1) * 4.0
  | eval (PCirculo(e1)) = 3.14 * 2.0 * (eval e1)
  | eval (PRetangulo(e1, e2)) = (2.0 * (eval e1)) + (2.0 * (eval e2))
  | eval (PTriangulo(e1, e2, e3)) = (eval e1) + (eval e2) + (eval e3);