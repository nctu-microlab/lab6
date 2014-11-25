  ORG 0
  jmp START
  
  ORG 03h
  jmp INT0
  
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
  
INT0:
  push A
  push PSW
  setb PSW.3
  mov R7, 8
  
LOOP1:
  mov A, #00h
  mov P1, A
  call DELAY
  mov A, #0FFh
  mov P1, A
  call DELAY
  djnz R7, LOOP1
  
  pop PSW
  pop A
  reti
  
DELAY:
  push 4
  push 5
  
  mov R5, #0FFh
D1:
  mov R4, #0FFh
  djnz R4, $
  djnz R5, D1
  
  pop 5
  pop 4
  ret
  
  END
