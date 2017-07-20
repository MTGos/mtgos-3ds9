#include "include/regs.h"
#include <base.hpp>
void print_regdump(cpu_state *state) {
    (*out << "r0: ").puti(state->r0);
    (*out << " r1: ").puti(state->r1);
    (*out << " r2: ").puti(state->r2);
    (*out << " r3: ").puti(state->r3);
    (*out << " r4: ").puti(state->r4);
    (*out << " r5: ").puti(state->r5);
    (*out << " r6: ").puti(state->r6);
    (*out << " r7: ").puti(state->r7);
    (*out << " r8: ").puti(state->r8);
    (*out << " r9: ").puti(state->r9);
    (*out << " r10: ").puti(state->r10);
    (*out << " r11: ").puti(state->r11);
    (*out << " r12: ").puti(state->r12);
    (*out << " pc: ").puti(state->pc);
    (*out << " cpsr: ").puti(state->cpsr);
    (*out << " sp: ").puti(state->sp);
    (*out << " lr: ").puti(state->lr);
    (*out << " returnAddr: ").puti(state->returnAddr);
    *out << "\n";
}
extern "C" cpu_state *handleINT(int number, cpu_state *state) {
    *out << "Interrupt";
    out->puti(number);
    *out << " occurred!\n";
    if (number != 4) {
        out->setColor(Color::RED);
        print_regdump(state);
        *out << "KERNEL PANIC: Unhandled CPU exception\n";
        for (;;);
    } else {
    }
    switch (number) {
    case 0:
    case 1:
    case 2:
    case 3:
        if (state->cpsr & 0x20)
            state->returnAddr -= 2;
        else
            state->returnAddr -= 4;
    }
    out->puti(state->cpsr);
    return state;
}
extern "C" void panic2(char *msg, cpu_state *state) {
    out->setColor(Color::RED);
    *out << "KERNEL PANIC: " << msg << "\n";
    print_regdump(state);
    for (;;)
        ;
}
