;ORG  0000H
;AJMP MAIN
;ORG  0100H


;MAIN:   	MOV    B, #10;    B <- 10，循环控制次数
			;MOV    R1, #50H;  R1 <- 50H，数列1的首地址
			;MOV    R0, #60H;  R0 <- 60H，数列2的首地址
			;MOV    A, #12H;   A <- 12H，用于数列赋值
			;MOV   DPTR, #0100H;DPTR <- 0100H，片外RAM目的地址
			
;LOOP1:		MOV    @R1, A;    将A赋值给R1装着的地址所指向的空间
			;INC    R1;        数列1地址加一
			;ADD    A, #11H;   A += 11H，目的是各个数据赋值不同
			;DJNZ   B, LOOP1;  循环控制次数, --B 若不为0则继续循环赋值
			
			;MOV    B, #10;    给B重新赋值
			
;LOOP2:		MOV    @R0, A;    将A赋值给R1装着的地址所指向的空间
			;INC    R0;        数列2地址加一
			;ADD    A, #14H;   A += 11H，目的是各个数据赋值不同
			;DJNZ   B, LOOP2;  循环控制条件, --B 若不为0则继续循环赋值
			
			;MOV    R0, #60H;  R0 <- 60H,给R0重新赋值
			;MOV    R1, #50H;  R1 <- 50H,给R1重新赋值
			
;LOOP3:		MOV    A, @R1;    将R1装着的地址所指向的内容赋值给A
			;SWAP   A;         A的高低四位交换
			;ANL    A, #0F0H;  将A低四位清零
			;MOV    R3, A;     R3 <- A, 将A的值暂存
			;MOV    A, @R0;    将R0装着的地址所指向的内容赋值给A
			;ANL    A, #0FH;   将A高四位清零
			;ORL    A, R3;     将A和R3相或,得到合字结果
			;MOVX   @DPTR, A;  将结果赋值给片外RAM
			;INC    R1;        数列1地址加一
			;INC    R0;        数列0地址加一
			;INC    DPTR;      片外RAM地址加一
			;DJNZ   B, LOOP3;  循环控制条件, --B 若不为0则继续循环赋值
			;SJMP   $;         结束指令
			;END
