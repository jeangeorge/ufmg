fun isInvalid(c: char) =
	c = #" "
	orelse c = #","
	orelse c = #"."
	orelse c = #"-";

fun split(f: string) =
	String.tokens isInvalid(f);
