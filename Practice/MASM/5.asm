STACK SEGMENT
	DW 10 DUP(?)
STACK ENDS

DATA SEGMENT
	FIRSTLINE  DB "IN   DATE xx/xx/xx TIME xx:xx",10,'$'
	SECOND     DB "OUT 	DATE xx/xx/xx TIME xx:xx",10,'$'
	THRID	   DB "TOTAL            DAYS (24 hours)",10,'$'
	FOUR	   DB "                 HOURS",10,'$'
	FIVE	   DB "COST             BAHT",'$'
	
	HANDLE DW ?
	FILENAME DB "file.txt"
	BUFFER DB 50,?,50 DUP(?)
	TEMP_DATA DW 0 
	DIFF_MONTH DW 0
	DIFF_DAYS DW 0
	DIFF_HOURS DW 0
	DIFF_MINUTE DW 0
	ALL_FEE DW 0
	ALL_HOURS DW 0
DATA ENDS

CODE SEGMENT
	ASSUME CS:CODE, DS:DATA, SS:STACK
	
_START PROC

	;load register data

	;open file
	LEA DX,FILENAME
	MOV AH,3H ;openfile
	MOV CX,0 ;normal mode
	INT 21H
	MOV HANDLE,AX ;store file handle in HANDLE
	
	;read data from file
	LEA DX,BUFFER
	MOV BX,HANDLE ;move handle file to BX
	MOV AH,3FH ;read data
	MOV CX,26 ;amount of byte that want to read
	INT 21H
	
	;copy xx/xx/xx and xx:xx string for display
	LEA DX,FIRSTLINE+10
	LEA DI,BUFFER
	MOV CX,8 ;amount byte that want to copy
	CALL COPY_STRING_BUFFER
	LEA DX,FIRSTLINE+24
	LEA DI,BUFFER+8
	MOV CX,5 ;amount byte that want to copy
	CALL COPY_STRING_BUFFER
	
	;second value: copy xx/xx/xx and xx:xx string for display
	LEA DX,SECOND+10
	LEA DI,BUFFER+13
	MOV CX,8 ;amount byte that want to copy
	CALL COPY_STRING_BUFFER
	LEA DX,SECOND+24
	LEA DI,BUFFER+21
	MOV CX,5 ;amount byte that want to copy
	CALL COPY_STRING_BUFFER
	
	;close file
	MOV AH,3EH
	INT 21H
	
	;read day
	LEA DI,BUFFER
	MOV CX,2 ;length of number day
	CALL NUM_TO_ASCII ;read first value
	MOV TEMP_DATA,AX ;copy first value to TEMP_DATA
	LEA DI,BUFFER+13
	MOV CX,2 ;length of number day
	CALL NUM_TO_ASCII ;read second value
	MOV DX,TEMP_DATA ;Store second to DX
	CALL FIND_DIFF ;find different between enter day and exit day
	MOV DIFF_DAYS,AX
	
	;read month
	LEA DI,BUFFER+3
	MOV CX,2 ;length of number month
	CALL NUM_TO_ASCII ;read first value
	MOV TEMP_DATA,AX ;copy first value to TEMP_DATA
	LEA DI,BUFFER+16
	MOV CX,2 ;length of number month
	CALL NUM_TO_ASCII ;read second value
	MOV DX,TEMP_DATA ;Store second to DX
	CALL FIND_DIFF ;find different between enter month and exit month
	MOV DIFF_MONTH,AX
	
	;read hours
	LEA DI,BUFFER+8
	MOV CX,2 ;length of number hours
	CALL NUM_TO_ASCII ;read first value
	MOV TEMP_DATA,AX ;copy first value to TEMP_DATA
	LEA DI,BUFFER+21
	MOV CX,2 ;length of number hours
	CALL NUM_TO_ASCII ;read second value
	MOV DX,TEMP_DATA ;Store second to DX
	CALL FIND_DIFF ;find different between enter hours and exit hours
	MOV DIFF_HOURS,AX

	;read minutes
	LEA DI,BUFFER+13
	MOV CX,2 ;length of number minutes
	CALL NUM_TO_ASCII ;read first value
	MOV TEMP_DATA,AX ;copy first value to TEMP_DATA
	LEA DI,BUFFER+24
	MOV CX,2 ;length of number minutes
	CALL NUM_TO_ASCII ;read second value
	MOV DX,TEMP_DATA ;Store second to DX
	CALL FIND_DIFF ;find different between enter minutes and exit minutes
	MOV DIFF_MINUTE,AX
	
	CALL FEE ;calculate all fee
	
	;display
	;print first_line
	LEA DX,FIRSTLINE
	CALL PRINT
	
	;print second line
	LEA DX,SECOND
	CALL PRINT
	
	;print third line
	MOV AX,DIFF_DAYS
	LEA DI,THRID+9
	CALL NUM_TO_ASCII ;convert number and store in string
	LEA DX,THRID
	CALL PRINT
	
	;print fourth line
	MOV AX,ALL_HOURS
	LEA DI,FOUR+9
	CALL NUM_TO_ASCII
	LEA DX,FOUR
	CALL PRINT
	
	MOV AX,ALL_FEE
	LEA DI,FIVE+9
	CALL NUM_TO_ASCII
	LEA DX,FIVE
	CALL PRINT
_START ENDP

COPY_STRING_BUFFER PROC
	;DX : address of string need to paste
	;CX : amount of byte that want to copy
	;LEA DI,BUFFER outside proc
	DEC CX ;decrease CX by 1 for go to address last character
LOOPCOPY:
	CMP CX,0
	JB RETURNPROC ;if CX < 0 JUMP to returnproc
	MOV AL, DI[CX]
	MOV DI[CX],AL
	JMP LOOPCOPY
	DEC CX ;decrease CX by 1
RETURNPROC:
	RET
COPY_STRING_BUFFER ENDP

FEE PROC
	CMP DIFF_MINUTE,0
	JE HOURCAL ;not plus 1 if has not minute
	ADD ALL_HOURS,1
HOURCAL:
	MOV AX,DIFF_HOURS
	ADD ALL_HOURS,AX ;add hour diff to sum hours
	CMP ALL_HOURS,7
	JAE COUNTISDAY ;if all_hours >= 7 jump to daycal
	MOV AL,[ALL_HOURS] ;move all_hours to AX for multiple
	MOV BL,20
	MUL BL ;AX = all_hour*20
	ADD ALL_FEE,AX ;add hours fee to all_fee
	JMP DAYCAL
COUNTISDAY:
	ADD ALL_FEE,140 ;add 140 baht to all_fee
DAYCAL:
	MOV AX,DIFF_DAYS
	MOV BL,140
	MUL BX ;AX = diff_days*140
	ADD ALL_FEE,AX ;add day fee to all_fee
MONTHCAL:
	MOV AX,DIFF_MONTH
	MOV BL,4200 ;4200=120*30
	MUL BL ;AX = diff_month*4200
	ADD ALL_FEE,AX ;add month fee to all_fee
FEE ENDP

READ_AND_FIND_DIFF PROC
	;read month
	LEA DI,BUFFER+3
	MOV CX,2 ;length of number month
	CALL NUM_TO_ASCII ;read first value
	MOV DX,AX ;copy first value to DX
	LEA DI,BUFFER+16
	MOV CX,2 ;length of number month
	CALL NUM_TO_ASCII ;read second value
	CALL FIND_DIFF ;find different between enter month and exit month
READ_AND_FIND_DIFF ENDP
	
FIND_DIFF PROC
	;AX is first value
	;DX is second value
	;and AX is return value
	CMP AX,DX
	JB LESSTHAN ;if AX below DX JUMP to LESSTHAN
	SUB AX,DX
	RET
	
LESSTHAN:
	SUB DX,AX
	MOV AX,DX
	RET
FIND_DIFF ENDP
	
NUM_TO_ASCII PROC
	;MOV AX, move number to AX outside PROC
	;LEA DI,address from outside proc
	MOV TMP,AX ;copy AX to TMP
	
	MOV BX,0 ;counter
	MOV CX,10
COUNT_N:
	SUB DX,DX ;DX = 0
	DIV CX ;AX/10
	INC BX
	CMP AX,0 
	JNE COUNT_N ;JUMP if it has something to divide
	
	MOV [DI]+BX,'$' ;set end string at last char
	DEC BX
	
TO_ASCII:
	MOV AX,TMP ;reset AX
	SUB DX,DX ;DX = 0
	DIV CX ;AX/10
	ADD DX,30H ;change num to ascii code
	MOV [DI]+BX,DL ;move ascii to string BUFFER
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
	
CODE ENDS
	END _START