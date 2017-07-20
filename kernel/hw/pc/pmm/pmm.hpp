#pragma once
#include <pmm.hpp>
#include <multiboot.h>
class PMM_MB: public PMM {
    protected:
        multiboot_info_t *mb_info;
        virtual auto isFree(phys_t addr) -> bool;
    public:
        PMM_MB()=delete;
        PMM_MB(multiboot_info_t *mb_info);
        virtual ~PMM_MB();
};
