#include "pmm.hpp"
PMM_MB::PMM_MB(multiboot_info_t *mb_info): PMM(0x1000), mb_info(mb_info) {}

PMM_MB::~PMM_MB() {}

auto PMM_MB::isFree(phys_t addr) -> bool {
    auto mmap = (multiboot_memory_map_t*)((uintptr_t)(mb_info->mmap_addr));
    bool free=false;
    for(uint32_t i=0;i<mb_info->mmap_length;i++) {
        if((mmap[i].addr > addr) || (mmap[i].addr + mmap[i].len < addr))
            continue;
        if(mmap[i].type != MULTIBOOT_MEMORY_AVAILABLE)
            return false;
        free=true;
    }
    if(!free)
        return false;
    if(addr == (phys_t)((uintptr_t)mb_info))
        return false;
    return PMM::isFree(addr);
}
