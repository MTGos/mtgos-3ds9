.align 4
.global _start
.extern start
.section .text.boot
_start:
    mrs r0, cpsr
    orr r0, r0, #0b111000000
    msr cpsr_c, r0 //Disable IRQs

    ldr sp, =kernel_stack //set stack
    //Set other stacks
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
    mov r1, r2
    orr r1, #0b10011 //SVC
    msr cpsr, r1
    ldr sp, =svc_stack
    orr r1, #0b11111 //SYS
    msr cpsr, r1
    ldr sp, =kernel_stack

    //Certain bootloaders put the interrupt vectors in ITCM.
    //We don't want to mess with ITCM, so we put it back
    mrc p15, 0, r0, c1, c0, 0
    orr r0, #(1<<13)
    mcr p15, 0, r0, c1, c0, 0
    //Start start
    blx start
.global enable_irqs
enable_irqs:
    mrs r0, cpsr
    bic r0, #0b111000000
    msr cpsr, r0
    bx lr
.section .bss
.align 16
.space 4096
fiq_stack:
.space 4096
irq_stack:
.space 4096
abt_stack:
.space 4096
und_stack:
.space 4096
svc_stack:
.space 4096
kernel_stack:
