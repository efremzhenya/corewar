.name "catbot"
.comment "i'am more sleep, jump and fork"

load:
	sti r1, %:live, %1
	sti r1, %:after, %1
	and r1, %0, r2
fork:
	fork %:live
after:
	live %1
	zjmp %:fork
live:
	live %1
	zjmp %-5
