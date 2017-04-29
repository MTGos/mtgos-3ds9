.arm
.arch armv6k
.fpu vfpv2
.align 4
.global _start
.extern start
.section .text.boot
_start:
    CPSID aif //Disable interrupts
    ldr sp,  =kernel_stack
    //Enable FPU
    mov r0, #0
    mov r1, #0xF00000
    mcr p15, 0, r1, c1, c0, 2
    mcr p15, 0, r0, c7, c5, 4
    mov r1, #0x40000000
    mov r2, #0x3C00000
    fmxr fpexc, r1
    fmxr fpscr, r2
    //Start MTGos
    blx start

.section .bss
.space 16384
kernel_stack:
