datatype Planeta = Mercurio
	| Venus
	| Terra
	| Marte
	| Jupiter
	| Saturno
	| Urano
	| Netuno;

fun years(m) = m div 12;

fun planetAge (m: int, Mercurio) = 88 * years(m)
	| planetAge (m: int, Venus) = 225 * years(m)
	| planetAge (m: int, Terra) = 365 * years(m)
	| planetAge (m: int, Marte) = 687 * years(m)
	| planetAge (m: int, Jupiter) = 4332 * years(m)
	| planetAge (m: int, Saturno) = 10760 * years(m)
	| planetAge (m: int, Urano) = 30681 * years(m)
	| planetAge (m: int, Netuno) = 60190 * years(m);