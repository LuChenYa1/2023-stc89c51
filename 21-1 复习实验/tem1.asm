		 ;ORG    0000H
		 ;SJMP   MAIN
		 ;ORG    0040H
;main:    MOV  30H, #86H
	     ;MOV  31H, #79H
	     ;MOV  A, 30H
		 ;ANL  A, #0FH
		 ;SWAP A
		 ;MOV  B, A;保存
		 ;MOV  A, 31H
		 ;ANL  A, #0FH
		 ;ORL  A, B
		 ;CJNE A, #99H, COMP
		 ;MOV  33H, A;等于
		 ;SJMP LOOP2
		 
;COMP:    JNC  LOOP1
	     ;MOV  32H, A;小于
		 ;SJMP LOOP2
		 
;LOOP1:   MOV  34H, A;大于		
	     ;SJMP LOOP2	
		
;LOOP2:	 SJMP $
		 ;END
	