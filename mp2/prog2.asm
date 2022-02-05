;Introduction
;This program does a "reverse polish notation" 
;1.The user types in numbers from 0-9, +-*/^,or "space" and =
;	A [CHECK_NUMBER] and [CHECK_OP] subroutines will check 
;	if the input is a number, operator or invalid.
;2.1.If the input is a number, It will be [PUSH]ed onto the stack, then back
;	 to input
;2.2.If the input is not a number, it will be checked if it is one
;	 of the following: +-*/^"space"= 
;2.3.{+-*/^=} will be continued, "space" will sent the program back to input
;3.1.For {+-*/^}, first two numbers will be poped from the stack,
; 	 the first number poped will be assigned R3 and the second R4,
;	 so it is always R4 operand R3. After it is done, push the number
;	 back onto the stack
;3.2.For =, first check if the stack have only one value. If true, 
;	 save that number to R5 and print it in Hex
;4.Exceptions: Under such cases, print"Invalid Expression"
;			1.Stack underflow (when poping numbers)
;			2.input character invalid(when[Check]is ran)
;			3.stack have not one value(when "=")
;R0 is for keeping the thing that is typed by the user, 
;	and holding the number after it is processed by the operand
;R1 is for tempery value holding, mostly used in getting the 
;	negitive
;partners:jinj2(me)
.ORIG x3000
	
ZERO .FILL x30
NINE .FILL x39
ADDI .FILL x2B
MINUS .FILL x2D
TIME .FILL x2E
DIVS .FILL x2F
POWS .FILL x5E
SPACE .FILL x20
EQUAL .FILL x3D
;your code goes here
LOOP
	GETC
	OUT

CHECK_NUMBER
	LD R1,ZERO; load 0 into R1
	ST R7,Save_R7
	JSR NEG   ;  set R1 to its negitive
	LD R7,Save_R7
	ADD R1,R1,R0
	BRn CHECK_OP
	LD R1,NINE; load 9 into R1
	ST R7,Save_R7
	JSR NEG   ;  set R1 to its negitive
	LD R7,Save_R7
	ADD R1,R1,R0
	BRp CHECK_OP
	JSR PUSH
	ADD R5,R5,#0
	BRn EXCEPT
	JSR LOOP

CHECK_OP
	
	
	
	











;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;R3- value to print in hexadecimal
PRINT_HEX

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;R0 - character input from keyboard
;R6 - current numerical output
;
;
EVALUATE

;your code goes here


;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;input R3, R4
;out R0
PLUS					;adds the value in R3 and R4
;your code goes here
	ADD,R0,R3,R4
	RET
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;input R3, R4
;out R0
MIN	
;your code goes here
	ADD,R1,R3,#0		;first set R3 to its negitive and put 
	ST R7,Save_R7
	JSR NEG				;it in R1, then add R1 to R4
	LD R7,Save_R7
	ADD,R0,R4,R1
	RET
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;input R3, R4
;out R0
MUL	
;your code goes here
	ADD R1,R3,#-1		;R4 adds to itself for (R3-1) times
	AND R0,R0,#0
LOOP_MUL
	ADD R0,R0,R4
	ADD R1,R1,#-1
	BRp LOOP_MUL
	RET
	
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;input R3, R4
;out R0
DIV	
;your code goes here
	AND R0,R0,#0
	ADD R1,R3,#0
	ST R7,Save_R7
	JSR NEG
	LD R7,Save_R7
LOOP_DIV
	ADD R4,R4,R3
	BRnz END_DIV
	ADD R0,R0,#1
	BRnzp LOOP_DIV
END_DIV
	RET
	
	
	
	
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;input R3, R4
;out R0
EXP
;your code goes here
	ADD R1,R3,#-1		;R4 times itself for (R3-1) times
	AND R0,R0,#0
	ADD R3,R4,#0
LOOP_EXP
	ST R7,Save_R7
	JSR MUL				;need to call MUV to do it 
	LD R7,Save_R7
	ADD R4,R0,#0
	ADD R1,R1,#-1
	BRp LOOP_EXP
	RET

	
;IN:R0, OUT:R5 (0-success, 1-fail/overflow)
;R3: STACK_END R4: STACK_TOP
;
PUSH	
	ST R3, PUSH_SaveR3	;save R3
	ST R4, PUSH_SaveR4	;save R4
	AND R5, R5, #0		;
	LD R3, STACK_END	;
	LD R4, STACk_TOP	;
	ADD R3, R3, #-1		;
	NOT R3, R3		;
	ADD R3, R3, #1		;
	ADD R3, R3, R4		;
	BRz OVERFLOW		;stack is full
	STR R0, R4, #0		;no overflow, store value in the stack
	ADD R4, R4, #-1		;move top of the stack
	ST R4, STACK_TOP	;store top of stack pointer
	BRnzp DONE_PUSH		;
OVERFLOW
	ADD R5, R5, #1		;
DONE_PUSH
	LD R3, PUSH_SaveR3	;
	LD R4, PUSH_SaveR4	;
	RET


PUSH_SaveR3	.BLKW #1	;
PUSH_SaveR4	.BLKW #1	;


;OUT: R0, OUT R5 (0-success, 1-fail/underflow)
;R3 STACK_START R4 STACK_TOP
;
POP	
	ST R3, POP_SaveR3	;save R3
	ST R4, POP_SaveR4	;save R3
	AND R5, R5, #0		;clear R5
	LD R3, STACK_START	;
	LD R4, STACK_TOP	;
	NOT R3, R3		;
	ADD R3, R3, #1		;
	ADD R3, R3, R4		;
	BRz UNDERFLOW		;
	ADD R4, R4, #1		;
	LDR R0, R4, #0		;
	ST R4, STACK_TOP	;
	BRnzp DONE_POP		;
UNDERFLOW
	ADD R5, R5, #1		;
DONE_POP
	LD R3, POP_SaveR3	;
	LD R4, POP_SaveR4	;
	RET
	
;In R1, out R1(but it is negitive)
NEG
	NOT R1,R1
	ADD R1,R1,#1
	RET
	
Save_R7     .BLKW #1
POP_SaveR3	.BLKW #1	;
POP_SaveR4	.BLKW #1	;
STACK_END	.FILL x3FF0	;
STACK_START	.FILL x4000	;
STACK_TOP	.FILL x4000	;


.END
