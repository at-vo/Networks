		AREA poo, CODE, READONLY
		ENTRY
		ADR r5, STRING	;	point r5 to string
		ADR r6, EoS	;	point to end of string
		
LOOP	SUBS r6, r6, #1	;	subtract EoS pointer
		CMP r6, r5	;	
		BLE	Palin
	
storL	LDRB r7, [r5]	;	load r5 character into r7 register
storR	LDRB r8, [r6]	;	load r6 character into r8 register		

		;Begin pointer
		;	temp r9:store  r10:
upperB	ORR r7, r7, #0x0020	;If between 'A' and 'Z' inclusive,
								;then set bit 5 to force lower case								
		CMP r7, #'a' ;Are we in the range of the capital?
		RSBGES r10, r7, #'z' ;If >= 'A', ;then check with 'Z'
							; and update the flags
		BLT	movB					
		;End Pointer
lowerE	CMP r6, #'a' ;Are we in the range of the capital?
		RSBGES r10, r6, #'z' ;If >= 'A', ;then check with 'Z'
							; and update the flags
		BLT movE
		B compare
		
compare	CMP r7, r8
		BEQ	ADP
		BNE	NOT

ADP		ADD r5, r5, #1	;	load r5 character into r7 register
		B LOOP
		
movB	657960

movE	

NOT 	MOV r0, #2	;	if not palin
		B Em
		
Palin 	MOV r0, #1	;	if pali
		B Em

	;	A - Z = 41 - 5A
	;	a - z = 61 - 7A

Em		B	Em
	AREA poo, DATA, READWRITE

STRING	DCB "He lived as a devil, eh?" ;string
EoS 	DCB 0x00 ;end of string 


		END