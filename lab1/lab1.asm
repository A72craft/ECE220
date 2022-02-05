.ORIG x3000
;R0 is the thing to be printed(digit)
;R1 is digit counter(how many printed)
;R2 is the inner counter
;R3 is the hex 
;R4 is A-10 and "0"
;R6 is negitive 9
;shifting to the left is times 2
	AND R3,R3,#0
	ADD R3,R3,#15
PRINT_HEX
	AND R1,R1,#0
	ADD R1,R1,#4
OUTER_LOOP
	AND R0,R0,#0
	AND R2,R2,#0
	ADD R2,R2,#4
;;;;;;;;;;;;;;;;;;;;;;;
INNER_LOOP
	ADD R0,R0,R0
	ADD R3,R3,#0
	BRn ADD_ONE
	ADD R0,R0,#0
	BRnzp INNER_LOOP_FIN
ADD_ONE
	ADD R0,R0,#1
INNER_LOOP_FIN
	ADD R3,R3,R3
	ADD R2,R2,#-1
	BRp INNER_LOOP
	BRnzp PRINT_STUFF
;;;;;;;;;;;;;;;;;;;;;;;;	
PRINT_STUFF
	LD R4,ZERO
	ADD R0,R0,R4
	LD R6,NINE
	NOT R6,R6
	ADD R6,R6,#1
	ADD R4,R6,R0
	BRnz NUMBERS
	ADD R0,R0,#7
	BRnzp PRINT_STUFF_FIN
NUMBERS

PRINT_STUFF_FIN
	OUT
	ADD R1,R1,#-1
	BRp OUTER_LOOP
	HALT
	
ZERO .FILL x30
NINE .FILL x39
A .FILL x41
.END
