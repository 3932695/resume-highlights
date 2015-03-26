TITLE minimal

; minimal.asm
; Prof. Bailey
; Fall 2013

; Adds two 16-bit unsigned integers.

INCLUDE Irvine16.inc
.8086

.data
array WORD 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15


.code
main PROC
	mov ax, @data	; load data segment register...
	mov ds, ax	; ...with location of our data
	
	mov si, 1
	mov bx, OFFSET array
	
	push si
	push bx
	push ax
	mov ax, 4
	mul si
	add ax, 2
	mov si, 2
	mul si
	mov si, ax
	mov dx, 0
	mov dx, [bx + si]

	call DumpRegs	; display all registers
	mov ax, 4C00h	; Set up DOS function 4C: exit with termination code...
	int 21h 	; ...exit
main ENDP
END main
