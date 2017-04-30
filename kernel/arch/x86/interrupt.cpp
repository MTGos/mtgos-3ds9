#include "../../hw/pc/8259/pic.hpp"
#include <base.hpp>
#include <regs.h>
void print_regdump(cpu_state *state) {
    (*out << "eax: ").puti(state->eax);
    (*out << " ebx: ").puti(state->ebx);
    (*out << " ecx: ").puti(state->ecx);
    (*out << " edx: ").puti(state->edx);
    (*out << " esi: ").puti(state->esi);
    (*out << " edi: ").puti(state->edi);
    (*out << " ebp: ").puti(state->ebp);
    (*out << " eip: ").puti(state->eip);
    (*out << " esp: ").puti(state->esp);
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
    state->esp = (uintptr_t)state;
    state->eip = state->intr;
    out->setColor(Color::RED);
    *out << "KERNEL PANIC: " << (char *)state->error << "\n";
    print_regdump(state);
    for (;;)
        ;
}
