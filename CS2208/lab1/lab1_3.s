		AREA lab1_3, CODE, READONLY
		ENTRY
		
		MOV r0,#2    ;Put 2 in register r0 
		MOV r1,#3    ;Put 3 in register r1 
		MOV r2,#7   ;Put 20 in register r2 
		MOV r3,#2    ;Put 2 in register r3 
		MOV r4,#2    ;Put 2 in register r4 

		MUL r5, r3, r4 ; multiply r3 and r4 store in r5
		SUB r5, r5, r2 ; subtract r5 from r2 store in r5
		ADD r5, r5, r1 ; add r0 and r2 store in r7
		ADD r5, r5, r0 ; add r7 and r1 store in r0
		
		END