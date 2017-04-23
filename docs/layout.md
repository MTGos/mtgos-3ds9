libk/ git submodule containing the (platform-indipendent) kernel library
kernel/
    arch/ architecture-dependant code/data
        arm/
            3ds/
            rpi/
        aarch64/
            rpi3/
        x86/
            pc/
        x86_64/
            pc/
    cpu/ Contains links to used hw and contains initialization code
        arm/
            arm7tdmi/
            …
            cortexa53-32/
        aarch64/
            cortexa53/
        x86/
            486/ (generic x86 cpu)
            …
            pentium4/ (current x86 cpu)
        x86_64/
            pentium4/ (generic x86_64 cpu)
            …
            skylake/ (current x86_64 cpu)
    hw/
        fpu/
            x87/
            vfp/
            sse/
            …
        timer/
            pit/
            …
        …

During Make period a kernel/curr_config.h gets generated that contains things like endianess, address space size, registers, etc
