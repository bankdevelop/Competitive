STACK SEGMENT
	DW 64 DUP(?)
STACK ENDS

DATA SEGMENT
	HEAD_TABLE DB "Food          Quantity         Price(Baht)", '$'
	FOOD_ROWS  DB "                                       ", '$'
	FOOD       DB "                Food             ",5 DUP(?), '$'
	DELIVERY   DB "                Delivery Fee     ",5 DUP(?), '$'
	TOTAL      DB "                Total            ",5 DUP(?), '$'
	
	BUFFER DB 50,?,50 DUP(?)
	PRICE DB 50 DUP(?) 
	AMOUNT DB 50 DUP(?)
	INDEX DB 0
DATA ENDS

CODE SEGMENT
	ASSUME CS:CODE, DS:DATA, SS:STACK
	
_START PROC
	CALL READ_STRING ;read number of food
	CALL ASCII_TO_NUM
	MOV INDEX,AX ;move number of food to INDEX
	
COLLECT:
	
	;read food_name and store in STACK
	;ต้องหาทางเก็บสตริงของชื่ออาหาร
	
	;read amount and store in AMOUNT
	CALL READ_STRING
	CALL ASCII_TO_NUM
	MOV [AMOUNT]+INDEX,AX
	
	;read price and store in PRICE
	CALL READ_STRING
	CALL ASCII_TO_NUM
	MOV [PRICE]+INDEX,AX
	
	DEC INDEX;decrease 1 round
	CMP INDEX,0
	JA COLLECT; if more than 0 jump to COLLECT
	
DISPLAY:
	;display information
	LEA DX,HEAD_TABLE
	CALL PRINT
	;..
	
	
_START ENDP
	
ASCII_TO_NUM PROC
	;MOV CX, move number of ASCII code
	;LEA DI, point DI to STRING read
	MOV AX,0
NEXT: 
	MOV SI,10
	IMUL SI ; DX:AX=AX*10
	SUB BX,BX
	MOV BL,[DI] ; get ASCII code
	SUB BX,30H
	ADD AX,BX ; update partial result
	INC DI
	LOOP NEXT
	RET
ASCII_TO_NUM ENDP
	
READ_STRING PROC
	LEA DX,BUFFER
	MOV AH,0AH
	INT 21H; read string
	
	SUB CH,CH
	MOV CL,BUFFER+1 ;move number of char read to CX (For ASCII_TO_NUM)
	
	LEA DI,BUFFER+2 ;point DI to string read (For ASCII_TO_NUM)
	ADD DX,2 ;point DX to string read
	RET
READ_STRING ENDP

PRINT PROC
	;LEA DX, from outside PROC
	MOV AH,9 ; display string
	INT 21H
	RET
PRINT ENDP
	
CODE ENDS
	END _START