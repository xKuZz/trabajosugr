.section .data
.macro linea
          # .int 1,1,1,1
          # .int 2,2,2,2
          # .int 1,2,3,4
          # .int -1,-1,-1,-1
          # .int 0xffffffff, 0xffffffff, 0xffffffff, 0xffffffff
           .int 0x08000000, 0x08000000, 0x08000000, 0x08000000
          # .int 0x10000000, 0x20000000, 0x40000000, 0x80000000
          .endm
lista:		.irpc i,12345678
          linea
          .endr

longlista:	.int (.-lista)/4
resultado:	.quad -1
formato: .ascii "suma = %llu = %llx hex\n\0"
.section .text

#_start:	.global _start
  main: .global main

	mov    $lista, %ebx
	mov longlista, %ecx
	call suma
	mov %eax, resultado
  mov %edx, resultado+4
  
  push resultado+4
  push resultado
  push resultado+4
  push resultado 
  push $formato 
  call printf # == printf(formato,resultado,resultado)
  add $20, %esp

	mov $1, %eax
	mov $0, %ebx
	int $0x80

suma:
  push %esi
	mov $0, %eax #acumulador a 0
	mov $0, %edx
  mov $0, %esi #indice a 0
bucle:
	add (%ebx,%esi,4), %eax
  jnc nocarry
  inc %edx

nocarry:
	inc       %esi
	cmp  %esi,%ecx
	jne bucle

	pop %esi
	ret
