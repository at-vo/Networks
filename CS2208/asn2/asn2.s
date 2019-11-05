		AREA asn2, CODE, READWRITE
		ENTRY
		;	r2 - string1 pointer
		;	r3 - string2 pointer	
		;	r4 - string1 character	
		;	r5 - string2 character	
		;	r6 - pointer to 'the' string	
		; 	r7 - 'the' pointer character	
		;	r8 - temp pointer to string1 character
		;	r9 - pointer to EoS
		;	r10 - end of 'the' string
		ADR r2, STRING1								;point r2 to string1
		ADR r3, STRING2								;point r3 to string2
		ADR r9, EoS									;point to end of string1
		
		;	check if first word is 'the'
		LDRB r4, [r2]								;load character of string1 to r4	
		B Tloop										;branch to 'the' loop
		
		;	Main Loop
Bloop	LDRB r4, [r2]								;load character of string1 to r4	
		CMP r4, #spc								;check if pointer at a space
		BEQ	Tloop									;if equal then go to 'the' loop
													;else
		CMP r4, r9									;check if at end of string1
		BEQ	leave									;leave loop if at end 
													;else								
Tloop	LDRB r4, [r2]								;load character of string1 to r4	
		CMP r4, #'t'								;compare letter of string1 with 't'
		LDRBEQ r4, [r2,#1]							;load character of string1 offset 1 to r4 to find h
		CMPEQ r4, #'h'								;compare letter of string1 with 'h'
		LDRBEQ r4, [r2,#2]							;load character of string1 offset 2 to r4 to find e
		CMPEQ r4, #'e'								;compare letter of string1 with 'e'
		BEQ test									;branch to test if equal
													;else if not the letter 't' then word is not 'the' so add letter to string2
													
store	STRB r4, [r3], #incr						;store the letter into string2 then increment r3
		ADD r2, r2, #incr							;increment pointer to string1
		B Bloop
		
test	LDRB r4, [r2, #3]							;load character of string1 offset 3 to r4 to find a space
		CMP r4, #spc								;check if pointer at a space
		ADDEQ r2, r2, #skip
		BEQ Tloop
		CMP r4, #nul								;check if pointer at end
		BEQ leave									;if null char then reached end of string1, so leave
		

leave	B leave										;end through loop

		;	DATA DIRECTIVES	
skp		EQU 0x3										;skip 'the'
spc		EQU 0x20									;constant for space character
STRING1 DCB "and the man said they must go"   		;String1 
EoS     DCB 0x00                              		;end of string1 
		ALIGN
STRING2 SPACE 0xFF                            		;just allocating 255 bytes

		END