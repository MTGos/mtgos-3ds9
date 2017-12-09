#include "vectorinit.hpp"
#include <base.hpp>
extern "C" {
extern uintptr_t branch_macro;
void data_abort();
void fast_irq();
void normal_irq();
void prefetch_abort();
void svc_call();
void undefined_op();
void flushAll();
}
void initVectors() {
    uintptr_t *vectors = (uintptr_t *)0x08000000;
    // branch_macro is a ldr pc, [pc,#-4], meaning it reads the following word as PC
    vectors[0] = branch_macro;
    vectors[1] = (uintptr_t)&normal_irq;
    vectors[2] = branch_macro;
    vectors[3] = (uintptr_t)&fast_irq;
    vectors[4] = branch_macro;
    vectors[5] = (uintptr_t)&svc_call;
    vectors[6] = branch_macro;
    vectors[7] = (uintptr_t)&undefined_op;
    vectors[8] = branch_macro;
    vectors[9] = (uintptr_t)&prefetch_abort;
    vectors[10] = branch_macro;
    vectors[11] = (uintptr_t)&data_abort;
    flushAll();
}
IRQ_IO::IRQ_IO() {
    initVectors();
    *((volatile uint32_t*)0x10001000)=~0;
    *((volatile uint32_t*)0x10001004)=~0;
}
IRQ_IO::~IRQ_IO() {}

void* IRQ_IO::handleIRQ(void *data) {
    //Call IRQ handlers until all IRQs are done.
    int bit;
    while((bit=__builtin_ffs(*((volatile int*)0x10001004)))) {
        data = handlers[bit-1](data);
        *((volatile int*)0x10001004)=(1<<(bit-1));
    }
    return data;
}

void IRQ_IO::mask(int number) {
    *((volatile int*)0x10001004)&=~(1<<number);
}
void IRQ_IO::unmask(int number) {
    *((volatile int*)0x10001004)|=1<<number;
}
static IRQ_IO irq;
__attribute__((constructor))
static void init_irq() {
    irqs = (IRQ*)&irq;
}
