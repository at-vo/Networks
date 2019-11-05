		AREA codetest, CODE, READONLY
		ENTRY
		ADR r0,table1   	;r0 points to source
							;(note pseudo-op ADR)
		ADR r1,table2   	;r1 points to the destination
		MOV r2,#2       	;2 blocks of 8 = 16 words (64 bytes)to move
		
Loop 	LDMFD r0!,{r3-r10}	;REPEAT Load 8 registers (r3 to r10)
		STMFD r1!,{r3-r10} 	;store the registers at their destination
		SUBS r2,r2,#1     	;decrement loop counter
		BNE Loop         	;UNTIL all 2 blocks of 8 registers moved

Inf  	B Inf

table1  DCB "abcdefgh12345678ABCDEFGH12345678"
		DCB "12345678asdfghjk12345678QWERTYUI"
		SPACE 64
table2  DCB 0x00
		
		END