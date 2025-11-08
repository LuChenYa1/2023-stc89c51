			ORG  0000H
			AJMP MAIN
			ORG  0100H
MAIN: 
			;一、先给片内RAM50H~5AH随机赋值
			  MOV   50H, #56H
			  MOV   51H, #50H
			  MOV   52H, #12H
			  MOV   53H, #78H
			  MOV   54H, #37H
			  MOV   55H, #89H
			  MOV   56H, #52H
			  MOV   57H, #04H
			  MOV   58H, #04H
 			  MOV   59H, #29H
 			  MOV   5AH, #67H
			  
			  ;配置子程序相关参数的值
			  MOV   A, #5AH;         尾地址
			  MOV   30H, #50H;       30H储存首地址
			  SUBB  A, 30H;          A得到循环次数
			  MOV   31H, A;          31H储存循环次数10
			  ACALL SORT;            调用子程序完成排序 
			  SJMP  $;				 结束指令

;调用子程序
SORT:
			 ;二、初始化
			  MOV   R6, 31H; 		 外循环控制次数
			
LOOP1:		  ;外循环,下面已经有DJNZ，所以这里不需要对循环次数减一
			  ;注意，进入内循环之前必须对以下相关参数重新初始化
			  MOV   R0, 30H; 		 初始比较地址
			  MOV   R7, 31H; 		 内循环控制次数
			  MOV   B, #00H;         将标志位清零,不能用CY作为标志位，它用在了CJNE中
			  
LOOP2:		  ;内循环,下面已经有DJNZ，所以这里不需要对循环次数减一
			  MOV   A, @R0;   		 将要比较大小的前者赋值给A
			  MOV   20H, R0;  		 20H作为中转站
			  MOV   R1, 20H ;        R1暂存前者地址
			  INC   R0;       		 R0储存后者地址
			  MOV   21H, @R0; 		 将要比较大小的后者赋值给21H,因为CJNE无法用@Rn
			  CJNE  A, 21H, NotEqual;令前者和后者比较，不相等则跳转NotEqual判断是否换位
			  
interrecycle: DJNZ  R7, LOOP2;		 判断9次内循环是否完毕，完毕就向下运行
			  DJNZ  B, OVER;         若标志位B为0，证明排序已经完成，不再进入外循环，跳转进入结束行
			  DJNZ  R6, LOOP1;		 判断9次外循环是否完毕，完毕则停止运行
OVER:		  SJMP  Finish;   		 结束运行命令
			
NotEqual:     JNB   PSW.7, exchange; 当前者大于后者，跳转执行换位程序_HuHuan
			  SJMP  interrecycle;    不跳转则结束当次循环，返回判断内循环是否结束
			
exchange:	  ACALL _HuHuan;         调用换位功能子程序
			  SJMP  interrecycle;    换位完成,结束当次循环，返回判断内循环是否结束
			
_HuHuan:      ;把两个地址的值互换
			  MOV   B, #01H;         一旦发生交换，就将标志位置一
			  XCH   A, @R0;			 将A中包含的前者和(R0)指向的后者进行互换
			  MOV   @R1, A;          将A中包含的后者赋值给R1中暂存的上一位地址
			  RET;     				 返回子程序
			
Finish:		  RET;                   返回子程序                  
			  END
			
			
