  ORG 0
  jmp START
  
  ORG 03h
  jmp INTT0
  
START:
  mov IE, #10000001b
  mov TCON, #00000001b
  mov SP, #60h
  
MAIN:
  mov R7, #8
  mov A, #7Fh
  
LOOP:
  mov P1, A
  call DELAY
  rr A
  djnz R7, LOOP
  jmp MAIN
  
INTT0:
  mov IE, #00000000b
  mov TCON, #0
  push ACC
  push PSW
  setb PSW.3
  mov R7, #8
  
LOOP1:
  mov A, #00h
  mov P1, A
  call DELAY
  mov A, #0FFh
  mov P1, A
  call DELAY
  djnz R7, LOOP1
  
  pop PSW
  pop ACC
  mov IE, #10000001b
  mov TCON, #1
  reti
  
DELAY:
  push 4
  push 5
  push 6

  mov R6, #10
D2:
  mov R5, #0FFh
D1:
  mov R4, #0FFh
  djnz R4, $
  djnz R5, D1
  djnz R6, D2
  
  pop 6
  pop 5
  pop 4
  ret
  
  END
