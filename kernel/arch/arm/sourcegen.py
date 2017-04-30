int_handler.write(
"""\
.arm
.fpu vfpv2
.global branch_macro
branch_macro:
    ldr pc, [pc, #-4] //Load the next word into PC
.global data_abort
data_abort:
    sub lr, #4
    push {r0-r12,lr}
    ldr r0, =0
    blx intr_common_handler
    pop {r0-r12,pc}
.global fast_irq
fast_irq:
    sub lr, #4
    push {r0-r12,lr}
    ldr r0, =1
    blx intr_common_handler
    pop {r0-r12,pc}
.global normal_irq
normal_irq:
    sub lr, #4
    push {r0-r12,lr}
    ldr r0, =2
    blx intr_common_handler
    pop {r0-r12,pc}
.global prefetch_abort
prefetch_abort:
    sub lr, #4
    push {r0-r12,lr}
    ldr r0, =3
    blx intr_common_handler
    pop {r0-r12,pc}
.global svc_call
svc_call:
    push {r0-r12,lr}
    ldr r0, =4
    blx intr_common_handler
    pop {r0-r12,pc}
.global undefined_op
undefined_op:
    push {r0-r12,lr}
    ldr r0, =5
    blx intr_common_handler
    pop {r0-r12,pc}

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
    push_regs.append("push {r1,r2,r3,r4,r5}")
    pop_regs.append("pop {r1,r2,r3,r4,r5}")
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
    for reg in ["fpsid","fpscr","fpexc"]:
        reg_struct.write("    uint32_t "+reg+";\n")
    for reg in ("d"+str(i) for i in range(16)):
        reg_struct.write("    double "+reg+";\n")
for i in range(13):
    reg_struct.write("    uint32_t r"+str(i)+";\n")
reg_struct.write("    uint32_t pc;\n};")

