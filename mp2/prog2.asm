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
	GETC			;get and print the character that is 
	OUT				;pressed by the keyboard

CHECK_NUMBER
	LD R1,ZERO ; load 0 into R1
	ST R7,Save_R7
	JSR NEG   			;Checks if the ASCII code for the input is smaller
	LD R7,Save_R7		;than the smallest number (x30), if true, check if
	ADD R1,R1,R0		;it is a operator 
	BRn CHECK_OP
	LD R1,NINE   
	ST R7,Save_R7		;hecks if the ASCII code for the input is bigger
	JSR NEG   			;than the biggest number (x39), if true, check if
	LD R7,Save_R7		;it is a operator, else push it to the stack
	ADD R1,R1,R0
	BRp CHECK_OP
	LD R1,ZERO
	ST R7,Save_R7		;minus the number by x30 so that it is a number in
	JSR NEG				;binary and not in Hex
	LD R7,Save_R7
	ADD R0,R1,R0
	ST R7,Save_R7
	JSR PUSH
	LD R7,Save_R7
	ADD R5,R5,#0		;branch to EXCEPT if something went wrong in PUSH
	BRp EXCEPT
	BRnzp LOOP			;After push, go back to LOOP and wait for input

CHECK_OP
;Check if it is "+"
	LD R1,ADDI   		;First take the negitive of the "+" ASCII
						;if the negitive plus the input is zero then
	JSR NEG   			;it means that the input is "+" and will go to
						;that subroutine
	ADD R1,R1,R0
	BRz PLUS
;Check if it is "-"
	LD R1,MINUS    		;First take the negitive of the "-" ASCII
						;if the negitive plus the input is zero then
	JSR NEG   			;it means that the input is "-" and will go to
						;that subroutine
	ADD R1,R1,R0
	BRz MIN
;Check if it is "*"
	LD R1,TIME    		;First take the negitive of the "*" ASCII
						;if the negitive plus the input is zero then
	JSR NEG   			;it means that the input is "*" and will go to
						;that subroutine
	ADD R1,R1,R0
	BRz MUL
;Check if it is "/"
	LD R1,DIVS    		;First take the negitive of the "/" ASCII
	ST R7,Save_R7		;if the negitive plus the input is zero then
	JSR NEG   			;it means that the input is "/" and will go to
	LD R7,Save_R7		;that subroutine
	ADD R1,R1,R0
	BRz DIV
;Check if it is "^"
	LD R1,POWS     
	ST R7,Save_R7		;First take the negitive of the "^" ASCII
	JSR NEG   			;if the negitive plus the input is zero then
	LD R7,Save_R7		;it means that the input is "^" and will go to
	ADD R1,R1,R0		;that subroutine
	BRz EXP
;Check if it is "space"
	LD R1,SPACE     	;First take the negitive of the " " ASCII
	ST R7,Save_R7		;if the negitive plus the input is zero then
	JSR NEG   			;it means that the input is " " and will go to
	LD R7,Save_R7		;that subroutine
	ADD R1,R1,R0
	BRz SPACE_OP
;Check if it is "="
	LD R1,EQUAL     	;First take the negitive of the "=" ASCII
	ST R7,Save_R7		;if the negitive plus the input is zero then
	JSR NEG   			;it means that the input is "=" and will go to
	LD R7,Save_R7		;that subroutine
	ADD R1,R1,R0
	BRz EQUAL_OP		;it is not any of those, so it must be a invalid
	BRnzp EXCEPT		;input
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

SPACE_OP
	BRnzp LOOP
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;	

EQUAL_OP
	LD R3, STACK_START	;
	LD R4, STACK_TOP	;
	ADD R1,R4,#1
	ST R7,Save_R7
	JSR NEG   			;Check if there is only one number left
	LD R7,Save_R7		;in the stack. If not, branch to EXCEPT
	ADD R1,R1,R3
	BRnp EXCEPT
	ST R7,Save_R7
	JSR POP   			;POP the number to R5,while double checking 
	LD R7,Save_R7		;that there are no errors occuring 
	ADD R5,R5,#0
	BRp EXCEPT
	ADD R5,R0,#0
	BRnzp PRINT_HEX
	
	
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
POP_TWO
	ST R7,Save_R7
	JSR POP
	LD R7,Save_R7			;POPs two numbers from the 
	ADD R5,R5,#0			;stack,the first number goes 
	BRp EXCEPT				;in R3 and the second R4
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
	ST R5,Save_R5		;This contains two loops, an outer
	AND R1,R1,#0		;one and an inner one. The inner one
	ADD R1,R1,#4		;moves the 4 leftmost bit on R5 onto R0,which
OUTER_LOOP				;will later be printed. The outer loop
	AND R0,R0,#0		;shifts to the left by 4 bit so it can be
	AND R2,R2,#0		;moved to R0
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
	LEA R0,EXCEPTION_MESSAGE		;print the message if 
	PUTS							;an exception occurs
	HALT
;your code goes here
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;input R3, R4
;out R0
PLUS					;pop and adds the value in R3 and R4
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
	LD R7,Save_R7		;saving the result in R2,R6
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
	BRz PUSH_RESULT		;call the sign in R2,R6
	ADD R1,R0,#0		;so that the output will be correct
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
	LD R7,Save_R7		;and store them in R2,R6
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
	ADD R1,R2,R1		;call the sign in R2,R6
	BRz PUSH_RESULT		;so that the output will be correct
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
	ADD R3,R3,#-1
	BRz EXP_ONE
	ADD R1,R3,#0		;R4 times itself for (R3-1) times
	AND R6,R6,#0
	ADD R3,R4,#0
LOOP_EXP
	AND R2,R2,#0
	ADD R2,R2,R3
LOOP_EXP_MUL
	ADD R6,R6,R4		;this is a altered version of the MUL
	ADD R2,R2,#-1		;subroutine
	BRp LOOP_EXP_MUL
	AND R4,R4,#0
	ADD R4,R6,#0
	ADD R1,R1,#-1
	BRz LOOP_END
	AND R6,R6,#0
	BRnzp LOOP_EXP
LOOP_END
	ADD R0,R6,#0
	BRnzp PUSH_RESULT
EXP_ONE
	AND R0,R0,#0		;the output will be x if x^1 occurs
	ADD R0,R0,R4
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
EXCEPTION_MESSAGE .STRINGZ "Invalid Expression"
.END
