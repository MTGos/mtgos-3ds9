.arm
.arch armv6k
.fpu vfpv2
.align 4
.global _start
.extern start
.section .text.boot
_start:
    CPSID aif //Disable interrupts
    ldr sp,  =svc_stack
    //set other stacks
    mrs r0, cpsr
    bic r2, r0, #0x1F
    mov r1, r2
    orr r1, #0b10001 //FIQ
    msr cpsr, r1
    ldr sp, =fiq_stack
    mov r1, r2
    orr r1, #0b10010 //IRQ
    msr cpsr, r1
    ldr sp, =irq_stack
    mov r1, r2
    orr r1, #0b10111 //Abort
    msr cpsr, r1
    ldr sp, =abt_stack
    mov r1, r2
    orr r1, #0b11011 //Undefined
    msr cpsr, r1
    ldr sp, =und_stack
    orr r1, #0b11111 //SYS
    msr cpsr, r1
    ldr sp, =kernel_stack
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
.align 16
.space 4096
irq_stack:
.space 4096
fiq_stack:
.space 4096
abt_stack:
.space 4096
und_stack:
.space 4096
svc_stack:
.space 4096
kernel_stack:
