		AREA question1, CODE, READONLY
		ENTRY
		MOV r4, #0	;	SUM 
		MOV r5, #0	;	COUNTER	
		ADR r0, UPC	;	r0 points to UPC	
LOOP	CMP r5, #12	;	Check if Counter - 12 = 0
		BEQ FLOOP	;	if counter = 0, then go to FLOOP (final loop)
		LDRB r3, [r0], #1	;	Load temporary pointer with UPC[offset COUNTER], then increment UPC
		SUB	r3, r3, #48	;	Subtract 48 from temp to convert from hex to decimal digit
		ADD r3, r3, r3, LSL #1	;	multiply odd digit number by 3
		ADD r4, r4, r3	;	add odd number to sum
		LDRB r3, [r0], #1	;	Load temp with UPC[offset COUNTER], increment counter
		SUB	r3, r3, #48	;	Subtract 48 from temp to convert from hex to decimal digit
		ADD r4, r4, r3	;	add temp to SUM
		ADD r5, r5, #2	;	increment counter
		B	LOOP	;	Send back to loop	
FLOOP	SUBS r4, r4, #10	;	subtract 10 from final sum until 0 or negative
		BEQ r01	;	if equal to 0, then sum is valid since sum is a multiple of 10.
		BLT	r00	;	if less than 0, then the sum is invalid since final sum mod 10 must equal 0 to be valid. Once it is less then it is not a multiple of 10.
		BGT	FLOOP	;	else, Loop again
r00		MOV r0, #0	;	UPC invalid.
quit	B	quit	;	quits the process once UPC is invalid.
r01		MOV r0, #1	;	UPC is valid.
UPC		DCB "060383328783"  ;	UPC string
		END