#pragma once
#include <stdint.h>
#include <irq.hpp>
void initVectors();
struct IRQ_IO: IRQ {
    IRQ_IO();
    virtual ~IRQ_IO();
    virtual void* handleIRQ(void *data);
    virtual void mask(int number);
    virtual void unmask(int number);
};
