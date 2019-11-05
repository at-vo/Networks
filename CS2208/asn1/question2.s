		AREA question2, CODE, READONLY
		ENTRY
		ADR r5, STRING	;	point r5 to beginning of string
		ADR r6, EoS	;	point to end of string (EoS)	
		
		;	main control loop
LOOP	SUBS r6, r6, #1	;	decrement EoS pointer to get last character
		CMP r6, r5	;	Check if ending pointer and beginning pointer cross; 
		BLE	PALIN	;	if it does then it's a palindrome, then break loop and call Palin
		
		;	Load initial characters
Opoint	LDRB r7, [r5]	;	load r5 (beginning) character into r7 register
		LDRB r8, [r6]	;	load r6 (end) character into r8 register	
		
		;	check pointer at beginning of string
		ORR r7, r7, #0x0020		;	force lower case
		CMP r7, #'a'	;	Are we in the range of the lowercase?
		RSBGES r9, r7, #'z'		;	If >= 'a', ;then check with 'z'
								;   and update the flags
		BLT movB	;	go to movB to increment beginning pointer
		
		;	check pointer at end of string
		ORR r8, r8, #0x0020		;	force lower case
		CMP    r8, #'a'       	;	Are we in the range of the lowercase?
		RSBGES r10, r8, #'z'   	;	If >= 'a', ;then check with 'z'
								;	and update the flags
		BLT LOOP	;	go to LOOP to decrement Ending pointer 
					;	and recheck the loaded bytes and skip the special characters
		
		;	compare pointer characters
		CMP r7, r8	;	check if r7 - r8 = 0
		BNE	NOT	;	if they are not then go to NOT operation and break loop
		ADD r5, r5, #1	;	else, increment beginning pointer 
		B LOOP
		
		;	skip special characters
movB	ADD r5, r5, #1	;	increment pointer right
		B Opoint	;	go to Beginning string comparison

		;	operations
NOT 	MOV r0, #2	;	if not palindrome, assign value 2 to r0
QUIT	B	QUIT	;	quits after finding it not a palindrome.	
PALIN 	MOV r0, #1	;	if palindrome, assign value 1 to r0

		;	data definitions
STRING	DCB "He lived as a devil, eh?" ;	string
EoS 	DCB 0x00 ;	end of string 
		END