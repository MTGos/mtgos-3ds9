#include <irq.hpp>
IRQ *irqs;
static void* do_nothing(void *a) {return a;}
IRQ::IRQ() {
    for(int i=0;i<MAX_IRQ;i++)
        handlers[i]=&do_nothing;
}
IRQ::~IRQ() {}
void* IRQ::handleIRQ(void *data) {return data;}

void IRQ::mask(int number) {};
void IRQ::unmask(int number) {};
