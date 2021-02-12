STACK SEGMENT
	DW 64 DUP(?)
STACK ENDS

DATA SEGMENT
	S1 DB 75,80,95,80
	S2 DB 5,20,0,15
	S3 DB 90,85,100,95
	S4 DB 65,55,70,45
	S5 DB 75,70,60,75
	
	INDEX_MIN DB 0
	STUDENT_SIZE DB 4
	TEMP DB 0
	SUM_TEMP DB 0
	STRING DB 'STUDENT ',1,' gets ',0,' points so grade is ','F','$'
DATA ENDS

CODE SEGMENT
	ASSUME CS:CODE,DS:DATA,SS:STACK
	
_START PROC
		MOV BL,0 ;count number of students
		MOV BH,5 ;number of students
		
		;init start index of Data Segment
		LEA DI,S1
		
	DO: 
		CALL AVERAGE
		CALL PRINT
		
		;plus STUDENT_SIZE offset for go to next student
		LEA DI,[DI]+STUDENT_SIZE 
		
		;check it is still in loop?
		INC BL ;increase BL by 1
		CMP BL, BH ; campare BL is equal 5?
		JE END_DO ; if it is true end loop
		JMP DO
	END_DO:
_START ENDP

AVERAGE PROC ;find average then return to SUM_TEMP
		MOV SUM_TEMP,0 ;init SUM_TEMP = 0
		MOV INDEX_MIN,1 ;init INDEX_MIN = 1
		MOV CX,3 ; loop 3 times
		MOV AX,[DI]
		MOV TEMP,AL
		
	FIND_MIN_VALUE:
		MOV AL,[DI]+INDEX_MIN ;move student point to AL
		CMP TEMP,AL ;compare current student
		JAE PLUS ; if temp >= current student point jump to plus
		ADD SUM_TEMP,AL
		JMP BEHIDE_LOOP
		
	PLUS:
		MOV DL,TEMP ; move temp to store at DL
		ADD SUM_TEMP,DL ; plus temp to SUM_TEMP
		MOV TEMP,AL ; move AL to current student point

	BEHIDE_LOOP:
		INC INDEX_MIN ;increase INDEX_MIN by 1
		LOOP FIND_MIN_VALUE
	RETURN:
		;find average from top 3 maximum student point
		MOV DX,3
		MOV AL,SUM_TEMP
		CBW
		DIV DX
		RET ;return to MAIN
AVERAGE ENDP

PRINT PROC
	;move average student point to STRING
	MOV AL,SUM_TEMP
	MOV [STRING]+15,AL
	
	;if GRADE
	MOV AL,90
	CMP SUM_TEMP,AL
	JAE GRADE_A ;if point >= 90 get grade A
	
	MOV AL,80
	CMP SUM_TEMP,AL
	JAE GRADE_B ;if point >= 80 get grade B	
	
	MOV AL,65
	CMP SUM_TEMP,AL
	JAE GRADE_C ;if point >= 80 get grade C
	
	MOV AL,50
	CMP SUM_TEMP,AL
	JAE GRADE_D ;if point >= 80 get grade D
	
	JMP PRINTOUT ; else get grade F(default STRING)
	
	GRADE_A:
		MOV [STRING]+36,'A'
		JMP PRINTOUT
	GRADE_B:
		MOV [STRING]+36,'B'
		JMP PRINTOUT
	GRADE_C:
		MOV [STRING]+36,'C'
		JMP PRINTOUT
	GRADE_D:
		MOV [STRING]+36,'D'
	
	PRINTOUT:
		LEA DX,[STRING]+37
		MOV AH,9 ; display string
		INT 21H
		
	;add student number to STRING
	INC [STRING]+8
	
	RET ;return
PRINT ENDP

CODE ENDS
	END _START