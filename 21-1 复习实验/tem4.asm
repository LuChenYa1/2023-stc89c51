			;ORG   0000H
			;AJMP  MAIN;      设置程序开始运行位置
			;ORG   0100H;     设置程序初始地址
				
;MAIN:   	;设置初始数据
			;MOV   R0, #50H;  R0 <- 50H
			;MOV   @R0, #12H; (50H) <- 13H 
			;MOV   R0, #53H;  R0 <- 53H 
			;MOV   @R0, #34H; (53H) <- 26H 
			;INC   R0;        R0 <- R0 + 1  
			;MOV   @R0, #56H; (54H) <- 49H
		
			;;一、拆字：将A中的值赋值给52H、51H，再分别清零
			;MOV   A, 50H;    A <- (50H)
			;MOV   52H, A;    (52H) <- A
			;SWAP  A;        AH <-> AL
			;MOV   51H, A;    (51H) <- A
			;ANL   52H, #0FH;  52H高位清零
			;ANL   51H, #0FH;  51H高位清零
			
			;;二、合字：把53H、54H的低位赋值给55H的高低位
			;MOV   A, 53H;    A <- (53H)
			;SWAP  A;         AH <-> AL
			;ANL   A, #0F0H;  A低位清零
			;MOV   55H, A;    (55H) <- A
			;MOV   A, 54H;    A <- (54H)
			;ANL   A, #0FH;   A高位清零
			;ORL   55H, A ;   (55H) <- (55H) | A
			
			;;四、与99H比较，根据结果放在不同内存单元
			;MOV   A, 55H;    A <- (55H)
		    ;CJNE  A, #99H, IfNotEqual;把A和99H进行比较，不相等就跳转
		    ;MOV   60H, A;    (60H) <- A
		    ;SJMP  Finish;    跳转结束语句，防止继续向下执行不必要的命令
			
;IfNotEqual: JNB   PSW.7, If99HSmall; CY == 1跳转，此时A <= 99H
			;MOV   61H, A;    (61H) <- A
			;SJMP  Finish;    跳转结束语句，防止继续向下执行不必要的命令
			
;If99HSmall: MOV   62H, A;  (62H) <- A
			;SJMP  Finish;    跳转结束语句，防止继续向下执行不必要的命令
			;;结束命令行
;Finish:	    SJMP  $
			;END
				