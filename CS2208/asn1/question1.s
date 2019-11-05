		AREA question1, CODE, READONLY
		ENTRY
		ADR r0, UPC	;	r0 points to UPC	
		;	main control loop
LOOP	CMP r5, #12	;	Check if Counter - 12 = 0
		BEQ FLOOP	;	if counter = 0, then go to FLOOP (final loop)
		;	odd number
		LDRB r3, [r0], #1	;	Load temporary pointer with UPC[offset COUNTER], then increment UPC
		SUB	r3, r3, #48	;	Subtract 48 from temp to convert from hex to decimal digit
		ADD r3, r3, r3, LSL #1	;	multiply odd digit number by 3
		ADD r4, r4, r3	;	add odd number to sum
		;	even number
		LDRB r3, [r0], #1	;	Load temp with UPC[offset COUNTER], increment counter
		SUB	r3, r3, #48	;	Subtract 48 from temp to convert from hex to decimal digit
		ADD r4, r4, r3	;	add temp to SUM
		ADD r5, r5, #2	;	increment counter
		B	LOOP	;	Send back to loop to add next next set of odd and even digits

		;	final loop
FLOOP	SUBS r4, r4, #10	;	subtract 10 from final sum until 0 or negative
		MOVEQ r0, #1	;	if equal to 0, then sum is valid since sum is a multiple of 10.
		MOVLT r0, #2	;	if less than 0, then the sum is invalid since final sum mod 10
						;	must equal 0 to be valid. Once it is less then it is not a multiple of 10.
		BGT	FLOOP	;	else, Loop again

		;	data definitions
UPC		DCB "060383328783"  ;	UPC string
		END