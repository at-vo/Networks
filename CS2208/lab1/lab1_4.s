		AREA lab1_3, CODE, READONLY
		ENTRY
		
		LDR r0, A ;Put A in register r0
		LDR r1, B; Put B in register r1
		LDR r2, C ;Put C in register r2
		LDR r3, D ;Put D in register r3
		LDR r4, E ;Put E in register r4
		MUL r6, r3, r4 ; multiply r3 and r4 store in r5
		SUB r5, r6, r2 ; subtract r5 from r2 store in r5
		ADD r5, r5, r1 ; add r0 and r2 store in r7
		ADD r5, r5, r0 ; add r7 and r1 store in r0
		STR r5, Z ; Store r5 at location Z
	
loop 	b loop
	
		AREA lab1_3, DATA, READWRITE
A		DCD 4 ;
B		DCD 12 ;
C		DCD -4 ;
D		DCD -2 ;
E		DCD -9 ;
Z 		DCD 0 ;
	
		END