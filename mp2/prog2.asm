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
;R2 is used in EXP as a inner 
;R3 is for the number at the top of the stack and STACK_START
;R4 is for the number at the second place of the stack and STACK_TOP
;R5 is for holding the final result and the exception for POP and PUSH
;R6 used when R4 in MUL or DIV is negitive
;R7 is for PC when JSR and RET in subroutines
;The Hex_print is a blackbox where it prints what ever is in R5
;partners:jinj2(me)
.ORIG x3000
ZERO .FILL x30
Save_R7     .BLKW #1
NINE .FILL x39
ADDI .FILL x2B
MINUS .FILL x2D
TIME .FILL x2A
DIVS .FILL x2F
POWS .FILL x5E
SPACE .FILL x20
EQUAL .FILL x3D
;your code goes here
LOOP
	AND R7,R7,#0
	GETC
	OUT

CHECK_NUMBER
	LD R1,ZERO ; load 0 into R1
	ST R7,Save_R7
	JSR NEG   ;  set R1 to its negitive
	LD R7,Save_R7
	ADD R1,R1,R0
	BRn CHECK_OP
	LD R1,NINE   ; load 9 into R1
	ST R7,Save_R7
	JSR NEG   ;  set R1 to its negitive
	LD R7,Save_R7
	ADD R1,R1,R0
	BRp CHECK_OP
	LD R1,ZERO
	ST R7,Save_R7
	JSR NEG
	LD R7,Save_R7
	ADD R0,R1,R0
	ST R7,Save_R7
	JSR PUSH
	LD R7,Save_R7
	ADD R5,R5,#0
	BRp EXCEPT
	BRnzp LOOP

CHECK_OP
;Check if it is "+"
	LD R1,ADDI   ; load the ASCII of "+" into R1
	ST R7,Save_R7
	JSR NEG   ;  set R1 to its negitive
	LD R7,Save_R7
	ADD R1,R1,R0
	BRz PLUS
;Check if it is "-"
	LD R1,MINUS    ; load the ASCII of "-" into R1
	ST R7,Save_R7
	JSR NEG   ;  set R1 to its negitive
	LD R7,Save_R7
	ADD R1,R1,R0
	BRz MIN
;Check if it is "*"
	LD R1,TIME    ; load the ASCII of "*" into R1
	ST R7,Save_R7
	JSR NEG   ;  set R1 to its negitive
	LD R7,Save_R7
	ADD R1,R1,R0
	BRz MUL
;Check if it is "/"
	LD R1,DIVS    ; load the ASCII of "/" into R1
	ST R7,Save_R7
	JSR NEG   ;  set R1 to its negitive
	LD R7,Save_R7
	ADD R1,R1,R0
	BRz DIV
;Check if it is "^"
	LD R1,POWS     ; load the ASCII of "^" into R1
	ST R7,Save_R7
	JSR NEG   ;  set R1 to its negitive
	LD R7,Save_R7
	ADD R1,R1,R0
	BRz EXP
;Check if it is "space"
	LD R1,SPACE     ; load the ASCII of "space" into R1
	ST R7,Save_R7
	JSR NEG   ;  set R1 to its negitive
	LD R7,Save_R7
	ADD R1,R1,R0
	BRz SPACE_OP
;Check if it is "="
	LD R1,EQUAL     ; load the ASCII of "=" into R1
	ST R7,Save_R7
	JSR NEG   ;  set R1 to its negitive
	LD R7,Save_R7
	ADD R1,R1,R0
	BRz EQUAL_OP
	BRnzp EXCEPT
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

SPACE_OP
	BRnzp LOOP
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;	

EQUAL_OP
	LD R3, STACK_START	;
	LD R4, STACK_TOP	;
	ADD R1,R4,#1
	ST R7,Save_R7
	JSR NEG   ;  set R1 to its negitive
	LD R7,Save_R7
	ADD R1,R1,R3
	BRnp EXCEPT
	ST R7,Save_R7
	JSR POP   ;  POP the last number in the stack
	LD R7,Save_R7
	ADD R5,R5,#0
	BRp EXCEPT
	ADD R5,R0,#0
	BRnzp PRINT_HEX
	
	
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
POP_TWO
	ST R7,Save_R7
	JSR POP
	LD R7,Save_R7
	ADD R5,R5,#0
	BRp EXCEPT
	ADD R3,R0,#0
	ST R7,Save_R7
	JSR POP
	LD R7,Save_R7
	ADD R5,R5,#0
	BRp EXCEPT
	ADD R4,R0,#0
	RET
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;R5- value to print in hexadecimal
PRINT_HEX
	ST R5,Save_R5
	AND R1,R1,#0
	ADD R1,R1,#4
OUTER_LOOP
	AND R0,R0,#0
	AND R2,R2,#0
	ADD R2,R2,#4
;;;;;
INNER_LOOP
	ADD R0,R0,R0
	ADD R5,R5,#0
	BRn ADD_ONE
	ADD R0,R0,#0
	BRnzp INNER_LOOP_FIN
ADD_ONE
	ADD R0,R0,#1
INNER_LOOP_FIN
	ADD R5,R5,R5
	ADD R2,R2,#-1
	BRp INNER_LOOP
	BRnzp PRINT_STUFF
;;;;;	
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
	LD R5,Save_R5
	HALT
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;
;
EXCEPT
	LEA R0,EXCEPTION_MESSAGE
	PUTS
	HALT
;your code goes here
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;input R3, R4
;out R0
PLUS					;adds the value in R3 and R4
;your code goes here
	ST R7,Save_R7
	JSR POP_TWO
	LD R7,Save_R7
	ADD R0,R3,R4
	BRnzp PUSH_RESULT
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;input R3, R4
;out R0
MIN	
;your code goes here
	ST R7,Save_R7
	JSR POP_TWO
	LD R7,Save_R7
	ADD R1,R3,#0		;first set R3 to its negitive and put 
	ST R7,Save_R7
	JSR NEG				;it in R1, then add R1 to R4
	LD R7,Save_R7
	ADD R0,R4,R1
	BRnzp PUSH_RESULT
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;input R3, R4
;out R0
MUL	
;your code goes here
	ST R7,Save_R7
	JSR POP_TWO			;pop two numbers
	LD R7,Save_R7
	ST R7,Save_R7
	JSR NEG_TEST		;test whether R3,R4 is negitive
	LD R7,Save_R7
	ADD R6,R6,#0
	BRzp MUL_R4_NEG
	ADD R1,R3,#0
	ST R7,Save_R7
	JSR NEG				
	LD R7,Save_R7
	ADD R3,R1,#0
MUL_R4_NEG
	ADD R2,R2,#0
	BRzp MUL_MID
	ADD R1,R4,#0
	ST R7,Save_R7
	JSR NEG				
	LD R7,Save_R7
	ADD R4,R1,#0
MUL_MID
	ADD R1,R3,#0		;R4 adds to itself for R3 times
	AND R0,R0,#0
LOOP_MUL
	ADD R0,R0,R4
	ADD R1,R1,#-1
	BRp LOOP_MUL

	ADD R1,R6,#0
	ST R7,Save_R7
	JSR NEG				
	LD R7,Save_R7
	ADD R1,R2,R1
	BRz PUSH_RESULT
	ADD R1,R0,#0
	ST R7,Save_R7
	JSR NEG				
	LD R7,Save_R7
	ADD R0,R1,#0
	BRnzp PUSH_RESULT
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;input R3, R4
;out R0
DIV	
;your code goes here
	ST R7,Save_R7
	JSR POP_TWO			;pop two numbers, R4/R3
	LD R7,Save_R7
	ST R7,Save_R7
	JSR NEG_TEST		;test whether R3,R4 is negitive
	LD R7,Save_R7
	ADD R6,R6,#0
	BRzp DIV_R4_NEG
	ADD R1,R3,#0
	ST R7,Save_R7
	JSR NEG				
	LD R7,Save_R7
	ADD R3,R1,#0
DIV_R4_NEG
	ADD R2,R2,#0
	BRzp DIV_MID
	ADD R1,R4,#0
	ST R7,Save_R7
	JSR NEG				
	LD R7,Save_R7
	ADD R4,R1,#0
DIV_MID
	AND R0,R0,#0		
	ADD R1,R3,#0		;set R0 to R3
	ST R7,Save_R7
	JSR NEG				;set R0(R3) to negitive
	LD R7,Save_R7
LOOP_DIV
	ADD R4,R4,R1
	BRn END_DIV
	ADD R0,R0,#1
	BRnzp LOOP_DIV
END_DIV
	ADD R1,R6,#0
	ST R7,Save_R7
	JSR NEG				
	LD R7,Save_R7
	ADD R1,R2,R1
	BRz PUSH_RESULT
	ADD R1,R0,#0
	ST R7,Save_R7
	JSR NEG				
	LD R7,Save_R7
	ADD R0,R1,#0
	BRnzp PUSH_RESULT
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;input R3, R4
;out R0
EXP
;your code goes here
	ST R7,Save_R7
	JSR POP_TWO			;pop two numbers from the stack to R3 and R4
	LD R7,Save_R7
	ADD R3,R3,#0
	BRz EXP_ZERO
	ADD R1,R3,#-1		;R4 times itself for (R3-1) times
	AND R0,R0,#0
	ADD R3,R4,#0
LOOP_EXP
	AND R2,R2,#0
	ADD R2,R2,R3
LOOP_EXP_IN
	ADD R0,R0,R4
	ADD R2,R2,#-1
	BRp LOOP_EXP_IN
	ADD R1,R1,#-1
	BRp LOOP_EXP
	BRnzp PUSH_RESULT
EXP_ZERO
	AND R0,R0,#0
	ADD R0,R0,#1
	BRnzp PUSH_RESULT
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
PUSH_RESULT ;in R0
	ST R7,Save_R7
	JSR PUSH				;push the number to the stack
	LD R7,Save_R7
	ADD R5,R5,#0
	BRp EXCEPT
	BRnzp LOOP
	
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;	
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

;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;input R3,R4, outputR2(R4),R6(R3) (1 when NEG, 0 when pos or zero)
NEG_TEST
	AND R6,R6,#0
	AND R2,R2,#0
	ADD R3,R3,#0
	BRzp NEG_TEST_R4
	NOT R6,R6
NEG_TEST_R4
	ADD R4,R4,#0
	BRzp NEG_TEST_END
	NOT R2,R2
NEG_TEST_END
	RET
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;



Save_R5     .BLKW #1
POP_SaveR3	.BLKW #1	;
POP_SaveR4	.BLKW #1	;
STACK_END	.FILL x3FF0	;
STACK_START	.FILL x4000	;
STACK_TOP	.FILL x4000	;
EXCEPTION_MESSAGE .STRINGZ "'Invalid Expression'"
.END
