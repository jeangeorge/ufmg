datatype expr = IConst of int 
  | Plus of expr * expr 
  | Minus of expr * expr
  | Multi of expr * expr
  | Div of expr * expr
  | Max of expr * expr
  | Min of expr * expr
  | Eq of expr * expr
  | Gt of expr * expr;

fun eval (IConst i) = i
  | eval (Plus(e1, e2)) = (eval e1) + (eval e2)
  | eval (Minus(e1, e2)) = (eval e1) - (eval e2)
  | eval (Multi(e1, e2)) = (eval e1) * (eval e2)
  | eval (Div(e1, e2)) = 
    if (eval e2) = 0 then
      0
    else (eval e1) div (eval e2)
  | eval (Max(e1, e2)) = 
    if (eval e1) > (eval e2) then
      (eval e1)
    else (eval e2)
  | eval (Min(e1, e2)) = 
    if (eval e1) < (eval e2) then
      (eval e1)
    else (eval e2)
  | eval (Eq(e1, e2)) = 
    if (eval e1) = (eval e2) then
      1
    else 0
  | eval (Gt(e1, e2)) = 
    if (eval e1) > (eval e2) andalso (eval e1) <> (eval e2) then
      1
    else 0;