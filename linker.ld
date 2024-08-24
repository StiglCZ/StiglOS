SECTIONS {
    . = 0x7E00;
    .text : {
        *(.text)
    }

    .data : {
        *(.data)
        *(.rodata)
    }

    .bss : {
        *(.bss)
    }
}

ENTRY(_start)
SEARCH_DIR(bin)
OUTPUT_FORMAT("binary")
