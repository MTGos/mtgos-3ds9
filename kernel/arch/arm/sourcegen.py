int_handler.write(
"""\
.arm
.fpu vfpv2
.section .bss
.space 4096
exception_stack:
.section .data
.space 4
oldsp:
.section .text
.global branch_macro
branch_macro:
    ldr pc, [pc, #-4] //Load the next word into PC
.macro interrupt_handler intid
    push {r0-r12,lr} //Push registers

    //Get previous sp and lr
    mrs r1, cpsr //Current mode
    mrs r0, spsr //Previous mode
    orr r0, #0xC0 //Disable interrupts in the previous mode
    bic r0, #0x20 //enable ARM mode in there

    //If the mode is user, switch to system mode
    and r2, r0, #0x1F
    cmp r2, #0x10
    bne 1f
    orr r0, #0x1F
1:
    //Change mode
    msr cpsr, r0
    mov r2, sp
    mov r3, lr
    //Switch back
    msr cpsr, r1
    mrs r0, spsr

    //Push those registers
    push {r0, r2, r3, lr}

    //Set argument 1
    ldr r0, =\intid

    //Jump to generic handler

    bl intr_common_handler

    //pop the special registers
    pop {r0, r3, r4, lr}
    tst r0, #0x20 //Is code ARM or thumb?
    beq 2f
    orr lr, lr, #1 //Enable thumb mode on return#
2:
    str lr, [sp, #0x34] //Set correct lr

    ldmfd sp!, {r0-r12, pc}^ //Return back to original mode
.endm
.global data_abort
data_abort:
    interrupt_handler 0
.global fast_irq
fast_irq:
    interrupt_handler 1
.global normal_irq
normal_irq:
    interrupt_handler 2
.global prefetch_abort
prefetch_abort:
    interrupt_handler 3
.global svc_call
svc_call:
    interrupt_handler 4
.global undefined_op
undefined_op:
    interrupt_handler 5

.extern handleINT
intr_common_handler:
""")
push_regs=[]
pop_regs=[]
if ("ENABLE_HARD" in config) and config["ENABLE_HARD"]:
    #Save the registers
    for i,j in enumerate(["fpsid","fpscr","fpexc"]):
        push_regs.append("fmrx r"+str(i+1)+", "+j)
        pop_regs.append("fmxr "+j+", r"+str(i+1))
    push_regs.append("push {r1,r2,r3}")
    pop_regs.append("pop {r1,r2,r3}")
    push_regs.append("vpush {d0-d15}")
    pop_regs.append("vpop {d0-d15}")
push_regs.append("mov r1, sp")
pop_regs.append("mov sp, r0")

for opc in push_regs:
    int_handler.write("    "+opc+"\n")
int_handler.write("    blx handleINT\n")
for opc in reversed(pop_regs):
    int_handler.write("    "+opc+"\n")
int_handler.write("    bx lr\n")

int_handler.write(".global panic\n.extern panic2\npanic:\n    push {r0-r12,lr}\n")
for opc in push_regs:
    int_handler.write("    "+opc+"\n")
int_handler.write("    b panic\n")

reg_struct.write("#include <stdint.h>\nstruct cpu_state {\n")
if ("ENABLE_HARD" in config) and config["ENABLE_HARD"]:
    for reg in ("d"+str(i) for i in range(16)):
        reg_struct.write("    double "+reg+";\n")
    for reg in ["fpsid","fpscr","fpexc"]:
        reg_struct.write("    uint32_t "+reg+";\n")
for reg in ["cpsr","sp","lr","returnAddr"]:
    reg_struct.write("    uint32_t "+reg+";\n")
for i in range(13):
    reg_struct.write("    uint32_t r"+str(i)+";\n")
reg_struct.write("    uint32_t pc;\n};")

