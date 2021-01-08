datatype btree = Leaf | Node of (btree * int * btree);

fun sumAll(Node (left, value, right)) = sumAll(left) + value + sumAll(right)
	| sumAll(Leaf) = 0;