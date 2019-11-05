	AREA final, CODE, READONLY         
		ENTRY
main    ADR   sp,  STACK          
		ADR   r1,  input         
		LDR   r0,[r1],#4         
		STR   pc,[sp,#4]!
call    B     fun1         
		STR   r0, [r1]
LOOP    B     
fun1    STMFA sp!,{r1,r2}         
		MOV r1,r0         
		MUL r2,r1,r0     
		MUL r0,r1,r2 
return  ldr r4, [sp, #-8]
		sub r4, #4
		mov pc, r4
	AREA final, DATA, READWRITE         
		DCD   0, 0, 0, 0 
STACK   DCD   0xFFFFFFFF         
		DCD   0, 0, 0, 0 
input   DCD 0x11 
output  DCD 0x00     
	END