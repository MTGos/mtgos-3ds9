.align 4
.global _start
.extern start
.section .text.boot
_start:
    mrs r0, cpsr
    orr r0, r0, #0x80
    msr cpsr_c, r0 //Disable IRQs
    //Flush instruction cache
    mov r0, #0
    mcr p15, 0, r0, c7, c5, 0

    //Use nintendos data cache flusher here, because I don't want to reverse it
    ldr r0, =0xFFFF0830
    blx r0

    //Disable caches and MPU
    mrc p15, 0, r0, c1, c0, 0 //read
    bic r0, r0, #(1<<12) //Disable instruction cache
    bic r0, r0, #(1<<2) //Disable data cache
    bic r0, r0, #(1<<0) //disable mpu
    mcr p15, 0, r0, c1, c0, 0 //write

    //clear caches again
    mov r0, #0
    mcr p15, 0, r0, c7, c5, 0
    ldr r0, =0xFFFF0830
    blx r0

    ldr sp, =kernel_stack //set stack

    //Configure ITCM to…something
    mrc p15, 0, r0, c9, c1, 1
    bic r0, #0b111110
    orr r0, #0b100010
    mcr p15, 0, r0, c9, c1, 1

    //Configure DTCM to address 0x30000000
    mrc p15, 0, r0, c9, c1, 0
    bic r0, #0b111110
    orr r0, #0b001010
    ldr r1, =0xFFFFF000
    bic r0, r1
    ldr r1, =0x30000000
    orr r0, r1
    mcr p15, 0, r0, c9, c1, 0

    //Enable both
    mrc p15, 0, r0, c1, c0, 0
    orr r0, r0, #(1<<18)
    bic r0, r0, #(1<<17)
    orr r0, r0, #(1<<16)
    mcr p15, 0, r0, c1, c0, 0

    //Give RW permissions to all memory regions
    ldr r0, =0x33333333
    mcr p15, 0, r0, c5, c0, 2 //Write Data
    mcr p15, 0, r0, c5, c0, 3 //Write instructions

    //Set MPU and caching
    ldr r0, =0xFFFF001F // ffff0000 64k bootrom
    ldr r1, =0x3000001B // 30000000 16k dtcm
    ldr r2, =0x00000035 // 00000000 128M ITCM
    ldr r3, =0x08000029 // 08000000 2M arm9 mem
    ldr r4, =0x10000029 // 10000000 2M IO mem
    ldr r5, =0x20000037 // 20000000 256M fcram
    ldr r6, =0x1FF00027 // 1FF00000 1M DSP
    ldr r7, =0x1800002D // 18000000 8M VRAM
    mcr p15, 0, r0, c6, c0, 0
    mcr p15, 0, r1, c6, c1, 0
    mcr p15, 0, r2, c6, c2, 0
    mcr p15, 0, r3, c6, c3, 0
    mcr p15, 0, r4, c6, c4, 0
    mcr p15, 0, r5, c6, c5, 0
    mcr p15, 0, r6, c6, c6, 0
    mcr p15, 0, r7, c6, c7, 0
    mov r0, #0b10101001 // unprot | arm9 | fcram | VRAM
    mcr p15, 0, r0, c2, c0, 0  // Data cacheable
    mcr p15, 0, r0, c2, c0, 1 // Instruction cacheable
    mcr p15, 0, r0, c3, c0, 0 // Data bufferable

    // Enable MPU and caching
    mcr p15, 0, r0, c3, c0, 0
    orr r0, r0, #(1<<12)
    orr r0, r0, #(1<<2)
    orr r0, r0, #(1<<0)
    mcr p15, 0, r0, c1, c0, 0

    //Start start
    blx start

.section .bss
.space 16384
kernel_stack:
