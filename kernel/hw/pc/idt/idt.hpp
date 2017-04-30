#pragma once
#include <stdint.h>
/**
 * Element of the interrupt descriptor table.
 */
struct IDT_entry {
    uint16_t offset0;    ///< bits 0…15 of interrupt entry address
    uint16_t selector;   ///< segment of the interrupt handler
    uint8_t zero;        ///< has to be zero
    uint8_t type : 4;    ///< Type of the interrupt
    bool storageSeg : 1; ///< 0 for interrupt gates (???)
    uint8_t dpl : 2;     ///< Priviledge level required for calling this interrupt
    bool used : 1;       ///< true if the entry is usable
    uint16_t offset1;    ///< Bits 16…31 of the entrypoint
#ifdef __x86_64__
    uint32_t offset2; ///< Bits 32…63 of the entrypoint. Only present on AMD64
    uint32_t zero2;   ///< Must be zero. Only present on AMD64
#endif
} __attribute__((packed));
void initIDT();
