		AREA question1, CODE, READWRITE
		ENTRY

		;	ini
		ADR r2, STRING1								;point r2 to string1
		ADR r3, STRING2								;point r3 to string2
		
		;	Main loop
loop	LDRB r4, [r2]								;load character of string1 to r4	
		CMP r4, #'t'								;compare letter of string1 with 't'
		LDRBEQ r4, [r2,#scd]						;if first character is 't' load character of string1 offset 1 to r4 to find h
		CMPEQ r4, #'h'								;compare letter of string1 with 'h'
		LDRBEQ r4, [r2,#thd]						;if second letter is 'h' load character of string1 offset 2 to r4 to find e
		CMPEQ r4, #'e'								;compare letter of string1 with 'e' then check terminating char of 'the' word
		LDRBEQ r4, [r2, #frt]						;if third letter is 'e' load character of string1 offset 3 to r4 to find a space
		CMPEQ r4, #spc								;check if pointer at a space, if it is, then the word is 'the'
		ADDEQ r2, r2, #skip							;so skip 3 characters in string1
		CMP r4, #nul								;else check if pointer at end
		BEQ leave									;if null char then reached end of string1, so leave
													;else if first letter is not 't', and second is not 'h',
													;and third is not 'e' and fourth is not a space,
													;then word is not 'the' so add letter to string2
store	LDRB r4, [r2], #incr						;load character of string1 offset 3 to r4 to find a space
		STRB r4, [r3], #incr						;store the letter into string2 then increment r3
		CMP r4, #spc								;check if at a space
		BEQ loop									;if at space then go back to Tloop to check for 'the'
		CMP r4, #nul								;check if null character
		BNE store									;if not then go back to store to check for another character 
													;else a null character
leave	B leave										;terminate with loop
		
		;	DATA DIRECTIVES	
		AREA question1, DATA, READWRITE
scd		EQU 1										;second letter of word offset
thd		EQU 2										;third letter of word offset
frt		EQU 3										;fourth letter of word offset
skip	EQU 3										;skip 'the' constant
incr	EQU 1										;constant for increment
spc		EQU 0x20									;constant for space character
nul		EQU 0x00									;constant for nul character
STRING1 DCB "and the man said they must go"  		;String1 
EoS     DCB 0x00                              		;end of string1 
		ALIGN
STRING2 SPACE 0xFF                            		;just allocating 255 bytes
		END
		