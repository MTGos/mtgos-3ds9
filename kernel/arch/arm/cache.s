.arm
.global drainWriteBuffer
drainWriteBuffer:
    mov r0, #0
    mcr p15, 0, r0, c7, c10, 4
    bx lr

.global flushAll
flushAll:
    mov r1, #0 //Segment
1:
        mov r0, #0 //Line
2:
            orr r2, r1, r0
            mcr p15, 0, r2, c7, c14, 2 //Flush current line
            add r0, #0x20 //Next line
            cmp r0, #0x400
            bne 2b
        add r1, #0x40000000
        cmp r1, #0x0
        bne 1b
    mov r0, #0
    mcr p15, 0, r0, c7, c5, 0 //flush instruction cache
    b drainWriteBuffer
