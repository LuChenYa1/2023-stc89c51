	 ;ORG    0000H
	 ;AJMP   MAIN
	 ;ORG    0100H
	 ;RS EQU 30H
;MAIN:MOV A, #7BH
	 ;MOV B, #100
	 ;DIV AB
	 ;MOV RS, A
	 ;MOV A, B
	 ;MOV B, #10
	 ;DIV AB
	 ;MOV RS+1, A
	 ;MOV RS+2, B
	 ;END
	