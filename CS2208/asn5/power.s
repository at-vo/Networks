		AREA power, CODE, READONLY
		ENTRY
		
		MOV r6, #nvar					;put n in register
		MOV r7, #xvar					;put x in register
		ADR sp, stack  					;define the stack
		MOV fp, sp						;move sp to fp
main	ADR r8, result					;point to result
		STMFD sp!,{r6-r8}				;store x, n and y (temp variable) in stack
		BL pow							;call power function	
		LDR r10, [fp,#Y]				;load final y from frame
		STR r10, [r8]					;store final y in result variable
		MOV sp,fp    					;restore the stack pointer
		LDR fp,[sp]  					;restore old frame pointer from the stack
		SWI 0x11 						;call O/S to terminate
		
pow		STMFD sp!,{fp,lr}				;store frame and link register on stack then update stack pointer
		MOV fp, sp						;fp point to base of frame
		SUB sp, sp, #Y_Spc	    		;move sp up 4 bytes for y
		LDR r9,[fp,#X_prev]  			;get x from previous stack frame
		STMFD sp!, {r9}					;push x on the stack and update sp
		LDR r9,[fp,#N_prev]  			;get n from previous stack frame
		CMP r9, #0						;compare n from previous with zero
		MOVEQ r10, #1					;move 1 to temp pointer if equal
		BEQ rest						;branch rest to restore
										;else
		STMFD sp, {r9}					;push n on the stack
		ANDS r9, r9, #1					;AND temp pointer with 1 to check if n is odd
		BEQ even						;if zero flag is updated n is even so branch to even
										;else n is odd so,
odd		LDR r9,[fp,#N]	 				;load n to temp
		SUB r9, r9, #1					;subtract 1 from n
		STMFD sp!, {r9}					;push n on the stack and increment stack pointer
		BL pow							;call power function with new n value
										;after power function recursion
		LDR r9,[fp,#Y]		  			;load y from next frame into temp pointer
		LDR r10, [fp,#X]				;load x from frame
		MUL r10, r9, r10				;muliply y from next frame with x and store in temp pointer
		B rest							;branch to rest to return
		
even	LDR r9, [fp,#N]	  				;load n to temp pointer
		LSR r9, r9, #1					;divide n by 2
		STMFD sp!, {r9}					;push n on the stack and increment stack pointer
		BL pow							;call power function with new n
										;after power function recursion
		LDR r9,[fp,#Y]		  			;load y from next frame into temp pointer
		MUL r10, r9, r9					;multiply y * y and store in temp pointer
										;now return
rest	STR r10, [fp,#return]			;store temp pointer in y(temp variable)
		MOV sp,fp       				;restore the stack pointer
		LDR fp,[sp]     				;restore old frame pointer from stack
		ADD sp, sp, #link 				;move stack pointer down 4 bytes to lr
		LDR lr, [sp]					;return by loading sp value to lr
		MOV pc,lr						;return to previous frame
		
		AREA power, DATA, READWRITE
Y_Spc	EQU 4							;space needed for return value Y
Y		EQU -4							;y in current frame
X		EQU -8							;x in current frame
N		EQU -12							;n in current frame
N_prev	EQU 8							;n in previous frame
X_prev	EQU 12							;x in previous frame
return	EQU 16							;return y to previous frame
link	EQU 4							;stack pointer to link register
xvar	EQU 2							;constant x
nvar	EQU 8							;constant n
		space 0x100						;stack space
stack 	DCB 0x00      					;Base of the stack
result	DCD 0xFF						;result variable
		END		