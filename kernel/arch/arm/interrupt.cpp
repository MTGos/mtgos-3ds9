#include <base.hpp>
#include <regs.hpp>
void print_regdump(cpu_state *state) {
    (*out << "r0: ").puti(state->r0);
    (*out << " r1: ").puti(state->r1);
    (*out << " r2: ").puti(state->r2);
    (*out << " r3: ").puti(state->r3);
    (*out << " r4: ").puti(state->r4);
    (*out << " r5: ").puti(state->r5);
}
