#pragma once
#include <pmm.hpp>
class PMM_MMAP: public PMM {
    protected:
        uint8_t bits;
        bool hostEndian;
        virtual auto isFree(phys_t addr) -> bool;
    public:
        PMM_MMAP();
        virtual ~PMM_MMAP();
};
