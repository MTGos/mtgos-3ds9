ENTRY(_start)
SECTIONS {
    . = 0x08000100;
    kernel_start = .;
    .text : {
        KEEP(*(.text.boot));
        *(.text)
    }
    .data : {
        start_ctors = .;
            KEEP(*(.init_array));
            KEEP(*(SORT_BY_INIT_PRIORITY(.init_array.*)));
            KEEP(*(.ctors));
        end_ctors = .;
        start_dtors = .;
            KEEP(*(.fini_array));
            KEEP(*(.fini_array.*));
            KEEP(*(.dtors));
        end_dtors = .;
        start_eh_frame = .;
            KEEP(*(.eh_frame));
            KEEP(*(.eh_frame.*));
        QUAD(0);
        KEEP(*(.gcc_except_table));
        KEEP(*(.gcc_except_table.*));
        *(.data)
    }
    .rodata : {
        *(.rodata)
    }
    .bss : {
        *(.bss)
        *(.bss.*)
        *(COMMON)
    }
    kernel_end = .;
}
