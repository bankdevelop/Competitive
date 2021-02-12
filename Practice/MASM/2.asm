; define
DATA SEGMENT
SALE DW 4250
POINT DW ?
REWARD DW ?
DATA ENDS

; code segment
CODE SEGMENT
ASSUME DS:DATA, CS:CODE
FIRST PROC

; หาค่า POINT
MOV AX, SALE
CWD ; ขยาย ax ให้เป็น DD เพื่อรองรับการหาร
MOV CX, 17
DIV CX ; หาร AX ด้วย 17 เพื่อหาค่าแต้มที่จะได้รับ
MOV POINT, AX ;นำผลหารไปใส่ไว้ใน POINT

;หาค่า REWARD - 2 เท่าของ POINT
MOV CL, 2
MUL CL ;คูณ AX ด้วย 2
MOV REWARD,AX ;นำค่าที่ได้ไปเก็บไว้ใน REWARD

FIRST ENDP
CODE ENDS
END FIRST