#define ASM_FILE 1
#include <config.h>
#include <multiboot.h>
.section .text.boot
.global _start
_start:
    jmp _start2
.align MULTIBOOT_HEADER_ALIGN
.int MULTIBOOT_HEADER_MAGIC
#ifndef ENABLE_FRAMEBUFFER
.int 0x0
.int -(MULTIBOOT_HEADER_MAGIC)
#else
.int 0x7
.int -(MULTIBOOT_HEADER_MAGIC+0x7)
.int 0,0,0,0,0
.int 0
.int 1024, 768, 24
#endif
.align MULTIBOOT_HEADER_ALIGN
.extern start
_start2:
    lgdt gdtr
    mov $0x10, %cx
    mov %cx, %ds
    mov %cx, %es
    mov %cx, %fs
    mov %cx, %gs
    mov %cx, %ss
    ljmp $0x08, $_start3
_start3:
    mov $kernel_stack, %esp //Initialize Stack
    push %ebx
    push %eax //Push arguments to start()
#ifdef ENABLE_FPU
    finit //Enable FPU
#endif
#ifdef ENABLE_SSE
    //Check for SSE
    mov $1, %eax
    cpuid
    test $1<<25, %edx
    jz _noSSE
    mov %cr0, %eax
    and $0xFFFB, %ax
    or $0x2, %ax
    mov %eax, %cr0
    mov %cr4, %eax
    or $3<<9, %ax
    mov %eax, %cr4
_noSSE:
#endif
    call start
_stop:
    cli
    hlt
    jmp _stop


.section .data
gdtr:
    .word 9 * 8
    .int gdt
gdt:
    .quad 0 //NULL
    //32-bit kernel code
    .word 0xFFFF
    .word 0x0000
    .byte 0x00
    .byte 0x9A
    .byte 0xCF
    .byte 0x00
    //32-bit kernel code
    .word 0xFFFF
    .word 0x0000
    .byte 0x00
    .byte 0x92
    .byte 0xCF
    .byte 00
    //32-bit user code
    .word 0xFFFF
    .word 0x0000
    .byte 0x00
    .byte 0xFA
    .byte 0xCF
    .byte 0x00
    //32-bit user data
    .word 0xFFFF
    .word 0x0000
    .byte 0x00
    .byte 0xF2
    .byte 0xCF
    .byte 00
    //64-bit kernel code
    .word 0xFFFF
    .word 0x0000
    .byte 0x00
    .byte 0x9B
    .byte 0xAF
    .byte 0x00
    //64-bit kernel code
    .word 0xFFFF
    .word 0x0000
    .byte 0x00
    .byte 0x93
    .byte 0xCF
    .byte 00
    //64-bit user code
    .word 0xFFFF
    .word 0x0000
    .byte 0x00
    .byte 0xFB
    .byte 0xAF
    .byte 0x00
    //64-bit user data
    .word 0xFFFF
    .word 0x0000
    .byte 0x00
    .byte 0xF3
    .byte 0xCF
    .byte 00
.section .bss
.space 16384
kernel_stack:
