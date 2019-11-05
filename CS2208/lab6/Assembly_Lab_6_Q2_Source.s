      AREA pipeline, CODE, READONLY
      ENTRY

      ADR sp,stack  ;define the stack
      MOV r1,#0x11
      MOV r2,#0x22
      MOV r3,#0x33
      MOV r4,#0x44
      MOV r5,#0x55
      MOV r6,#0x66
      MOV r7,#0x77
      
	  STMDA   sp!,{r1-r5}
	  STMDA	  sp!,{r6-r7}		; your 1st block move instruction
	  LDMIB   sp!,{r1-r7}				; your 2nd block move instruction
						; your 3rd block move instruction
Loop  B     Loop

      AREA pipeline, DATA, READWRITE
      SPACE 0x1C
stack DCD   0x00    ;TOS
      SPACE 0x1C
      END