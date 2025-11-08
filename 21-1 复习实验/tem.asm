		;ORG    0000H
		;LJMP   MAIN
		;ORG    0003H
		;AJMP   PINT0
		;ORG    0040H
;MAIN:   ;程序一：汇编实现外部中断单键控制单LED
		;SETB   PX0;   优先级
		;SETB   IT0;   触发方式
		;SETB   EX0;   允许INT0
		;SETB   EA;    总允许  
	    ;SJMP   $
	    
			
;PINT0:  ACALL  DELAY; 调用延时子程序 
		;CPL    P0.1;  触发中断，点灯 
		;RETI;         返回子程序
		
;;延时子程序，可随时调用该模块
;DELAY:  MOV    R4, #249
;D1:     NOP
		;NOP
		;DJNZ   R4,D1
		;NOP
		;RET
		
		;END
			