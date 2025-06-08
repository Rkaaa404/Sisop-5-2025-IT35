; kernel.asm

global _putInMemory
global _interrupt
global _getBiosTick
global _getCursorPos

; returns (row << 8) | col
_getCursorPos:
    push bp
    mov bp, sp
    mov ah, 0x03    ; BIOS function to get cursor position
    mov bh, 0x00    ; Page number 0
    int 0x10        ; Call video interrupt
    mov ax, dx      ; Move the result from DX (DH=row, DL=col) to AX for return
    pop bp
    ret
	
; unsigned int getBiosTick()
_getBiosTick:
    mov ah, 0x00
    int 0x1A
    mov ax, dx
    mov dx, cx
    ret

; void putInMemory(int segment, int address, char character)
_putInMemory:
	push bp
	mov bp,sp
	push ds
	mov ax,[bp+4]
	mov si,[bp+6]
	mov cl,[bp+8]
	mov ds,ax
	mov [si],cl
	pop ds
	pop bp
	ret

; int interrupt(int number, int AX, int BX, int CX, int DX)
_interrupt:
	push bp
	mov bp,sp
	mov ax,[bp+4]
	push ds
	mov bx,cs
	mov ds,bx
	mov si,intr
	mov [si+1],al
	pop ds
	mov ax,[bp+6]
	mov bx,[bp+8]
	mov cx,[bp+10]
	mov dx,[bp+12]

intr:	int 0x00

	mov ah,0
	pop bp
	ret
