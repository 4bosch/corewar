.name "heartbeat"
.comment "Gonna beat you with my heart"

str			1, 14
add			r8, r8, r8
fork		%11
live		%0
zjmp		%-5
live		%0
ld			12, r2
ld			%506, r3
sti			r2, r3, %0
ld			16, r4
sti			r4, r3, %0
add			r8, r8, r8
zjmp		%470
