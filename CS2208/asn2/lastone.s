		AREA lastone, CODE, READONLY
		ENTRY
		
		ADR r1, STRING1;load test case
		ADR r2, STRING2;load empty string
		
													;checks each word in string1 char by char till "the" is found	
check 	LDRB r4, [r1]								; load first char in string1 of current word
		cmp r4, #'t' 								; check for t in string1		
		LDRBEQ r4, [r1, #1]							; load next char in string1 only if t is first char in the current word 
		cmpeq r4, #'h'								;	 check for h in	string1	
		LDRBEQ r4, [r1, #2]							; load next char in string1 only if h is second char in the current word
		cmpeq r4, #'e'								;	 check for e in string1		
		
		beq checkSoN; if all cases are true check last char if its a space or null
		bne store; if not store the word in new string
	
; checks to see if the "the" word found terminates in EoS or space
checkSoN	LDRB r4, [r1, #3]; load fourth char in string1
			
			cmp r4, #' ';	 check for space in string1
			addeq r1, r1, #4; increment pointer to next char in string1 if space is the current char
			beq check; go back and check next word
			
			cmp r4, #0x00; if not a space then check if the last char is an EoS char
			beq quit; if so quit, if not go on to store the word

; stores the non "the " word
store 	ldrb r4, [r1], #1; load character to store then increment pointer to next char
		strb r4, [r2], #1; store the charecter in an empty byte, then increment to next empty byte
		
		cmp r4, #' '; compares the current char stored is a space
		beq check; if so go back and check next word
		cmp r4, #0x00; checks to see if current char stored is an EoS char
		bne store ; if neither compares are true, continue storing since current word is not fully stored
		;if EoS char is reached, branch to quit and end the program

quit	b	quit; infinite loop to end the end program

		
		AREA lastone, DATA, READWRITE
STRING1		DCB "and the man said they must go" ;String1
EoS			DCB 0x00 ;end of string1
STRING2 	SPACE 0xFF
		end
