		AREA pipe, CODE, READONLY
		  
		ADR   sp,stack     ;define the stack
		MOV   r0,pc
		STR   pc,[sp,#-4]!
		STMFD sp!,{pc}
Loop  	B     Loop
		
		AREA pipe, DATA, READWRITE
		SPACE 0x20         ;Stack body
stack 	DCD   0x00         ;TOS
		DCB 0x23

		END