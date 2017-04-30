#include "../../hw/pc/8259/pic.hpp"
#include <base.hpp>
#include <regs.h>
void print_regdump(cpu_state *state) {
    (*out << "rax: ").puti(state->rax);
    (*out << " rbx: ").puti(state->rbx);
    (*out << " rcx: ").puti(state->rcx);
    (*out << " rdx: ").puti(state->rdx);
    (*out << " rsi: ").puti(state->rsi);
    (*out << " rdi: ").puti(state->rdi);
    (*out << " rbp: ").puti(state->rbp);
    (*out << " rip: ").puti(state->rip);
    (*out << " rsp: ").puti(state->rsp);
    (*out << " r8: ").puti(state->r8);
    (*out << " r9: ").puti(state->r9);
    (*out << " r10: ").puti(state->r10);
    (*out << " r11: ").puti(state->r11);
    (*out << " r12: ").puti(state->r12);
    (*out << " r13: ").puti(state->r13);
    (*out << " r14: ").puti(state->r14);
    (*out << " r15: ").puti(state->r15);
    *out << "\n";
}
extern "C" void panic2(cpu_state *state);
extern "C" cpu_state *handleINT(cpu_state *state) {
    *out << "Interrupt ";
    out->puti(state->intr);
    *out << " occurred!\n";
    if (state->intr < 32) {
        out->setColor(Color::RED);
        print_regdump(state);
        *out << "KERNEL PANIC: Unhandled CPU exception\n";
        for (;;)
            ;
    }
    return state;
}
extern "C" void panic2(cpu_state *state) {
    state->rsp = (uintptr_t)state;
    state->rip = state->intr;
    out->setColor(Color::RED);
    *out << "KERNEL PANIC: " << (char *)state->rdi << "\n";
    print_regdump(state);
    for (;;)
        ;
}
