STACK SEGMENT
	DW 10 DUP(?)
STACK ENDS

DATA SEGMENT
	HEAD_TABLE DB "Food          Quantity         Price(Baht)", 10,'$'
	FOOD       DB "                Food             ",'$'
	DELIVERY   DB "                Delivery Fee     ",'$'
	TOTAL_TXT  DB "                Total            ",'$'
	NEWLINE	   DB 10, '$'
	
	TOTAL 	 DW 0
	FEE		 DW 0
	INDEX 	 DW 0
	N_FOOD 	 DW 0
	DISTANCE DW 0
	TMP      DW 0
	
	BUFFER 	 	  DB 50,?,50 DUP(?) 
	PRICE 	 	  DW 50 DUP(?)
	AMOUNT 	 	  DW 50 DUP(?)
	FOOD_NAME_ARR DB 256 DUP(?)
	FOOD_POINTER  DW ?
DATA ENDS

CODE SEGMENT
	ASSUME CS:CODE, DS:DATA, SS:STACK
	
_START PROC
	LEA DX,BUFFER
	CALL READ_STRING ;read number of food
	CALL ASCII_TO_NUM
	MOV INDEX,0 ;move number of food to INDEX
	MOV N_FOOD,AX ;move number of food to N_FOOD
	
	;init food array pointer
	LEA DX,FOOD_NAME_ARR
	MOV FOOD_POINTER,DX
	
COLLECT:
	;read food_name and store in STACK
	MOV DX,FOOD_POINTER
	MOV [FOOD_POINTER],22 ;FOOD_NAME_ARR[i] can handle 22 char
	CALL READ_STRING
	MOV [FOOD_POINTER]+21,'$' ;set end string
	
	;read amount and store in AMOUNT
	LEA DX,BUFFER
	CALL READ_STRING
	CALL ASCII_TO_NUM
	MOV BX,INDEX
	MOV AMOUNT[BX],AX ;store amount wait for display
	
	;read price and store in PRICE
	LEA DX,BUFFER
	CALL READ_STRING
	CALL ASCII_TO_NUM
	MUL AMOUNT[BX] ;multiple price with amount
	ADD TOTAL,AX ;add price to sum price
	MOV PRICE[BX],AX ;store price wait for display
	
	ADD FOOD_POINTER,24 ;move point to next slot
	
	INC INDEX ;increase 1 round
	MOV AX,INDEX
	CMP AX,N_FOOD
	JB COLLECT ;if less than N_FOOD jump to COLLECT
	
	;read distance
	LEA DX,BUFFER
	CALL READ_STRING
	CALL ASCII_TO_NUM
	MOV DISTANCE,AX
	
DISPLAY:
	CALL DELIVER_FEE
	;display head table
	LEA DX,HEAD_TABLE
	CALL PRINT
	
	MOV INDEX,0 ;reset index
	LEA DI,FOOD_NAME_ARR
PRINT_FOOD:
	;print food_name
	MOV DX,DI
	CALL PRINT
	ADD DI,24
	
	;print amount
	MOV BX,INDEX
	LEA DX,AMOUNT[BX]
	CALL PRINT
	
	;print price
	MOV BX,INDEX
	LEA DX,PRICE[BX]
	CALL PRINT
	
	;newLINE
	CALL PRINT_NEWLINE
	
	INC INDEX
	MOV AX,INDEX
	CMP AX,N_FOOD
	JE QUITLOOP ;jump if INDEX = N_FOOD 
QUITLOOP:
	;print food TOTAL
	LEA DX,FOOD
	CALL PRINT
	MOV AX,TOTAL
	CALL NUM_TO_ASCII
	CALL PRINT_BUFFER
	CALL PRINT_NEWLINE
	
	;print delivery fee
	LEA DX,DELIVERY
	CALL PRINT
	MOV AX,FEE
	CALL NUM_TO_ASCII
	CALL PRINT_BUFFER
	CALL PRINT_NEWLINE
	
	;print total
	MOV AX,FEE
	ADD TOTAL,AX ;add fee to TOTAL
	LEA DX,TOTAL_TXT
	CALL PRINT
	MOV AX,TOTAL
	CALL NUM_TO_ASCII
	CALL PRINT_BUFFER
_START ENDP

DELIVER_FEE PROC
FIVE:
	CMP DISTANCE,5
	JA MORE_FIVE ;jump if distance more than 5
	
	MOV AX,10 ;price per kilo
	MUL DISTANCE
	ADD FEE,AX ;move result to FEE
	RET ;return
	
MORE_FIVE:
	CMP DISTANCE,20
	JA MORE_TWENTY ;jump if distance more than 20

	CMP TOTAL,500
	JA MORE_FIVE_NEXT ;jump if sum price more than 500
	SUB DISTANCE,5
	ADD TOTAL,50 ;add first 5 kilo fee
	MORE_FIVE_NEXT:
		MOV AX,15 ;price per kilo
		MUL DISTANCE
		ADD FEE,AX
		RET

MORE_TWENTY:
	CMP TOTAL,500
	JA MORE_TWENTY_NEXT ;jump if sum price more than 500
	SUB DISTANCE,20
	ADD TOTAL,50 ;add first 5 kilo fee
	MORE_TWENTY_NEXT:
		ADD FEE,225 ;add 6-20 kilo fee
		MOV AX,20 ;price per kilo
		MUL DISTANCE
		ADD FEE,AX
		RET
DELIVER_FEE ENDP
	
NUM_TO_ASCII PROC
	;MOV AX, move number to AX outside PROC
	MOV TMP,AX ;copy AX to TMP
	
	MOV BX,0 ;counter
	MOV CX,10
COUNT_N:
	SUB DX,DX ;DX = 0
	DIV CX ;AX/10
	INC BX
	CMP AX,0 
	JNE COUNT_N ;JUMP if it has something to divide
	
	MOV [BUFFER]+BX,'$' ;set end string at last char
	DEC BX
	
TO_ASCII:
	MOV AX,TMP ;reset AX
	SUB DX,DX ;DX = 0
	DIV CX ;AX/10
	ADD DX,30H ;change num to ascii code
	MOV [BUFFER]+BX,DL ;move ascii to string BUFFER
	DEC BX
	CMP BX,0
	JAE TO_ASCII ;if BX has equal or more than 0 JUMP TO_ASCII
	RET
NUM_TO_ASCII ENDP

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
	;LEA DX, outside proc
	MOV AH,0AH
	INT 21H ;read string
	
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

PRINT_BUFFER PROC
	LEA DX,BUFFER
	CALL PRINT
	RET
PRINT_BUFFER ENDP

PRINT_NEWLINE PROC
	LEA DX,NEWLINE
	CALL PRINT
	RET
PRINT_NEWLINE ENDP
	
CODE ENDS
	END _START