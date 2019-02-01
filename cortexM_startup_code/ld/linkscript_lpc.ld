/*
 * Unified Cortex Startup - GNU ld linker script file
 *
 * This file is in public domain
 *
 * Put together by Paul Sokolovsky based on article by Vanya Sergeev
 * http://dev.frozeneskimo.com/notes/cortex_cmsis/ , GNU ld documentation
 * and numerous other public resources.
 *
 */

ENTRY(Reset_Handler)

SECTIONS {

    .text :
    {
        KEEP(*(.vectors))
        KEEP(*(.cortex_vectors))
        KEEP(*(.vendor_vectors))
        *(.text*)
        *(.rodata*)
        _end_text = .;
    } >flash

    /* http://sourceware.org/binutils/docs/ld/Output-Section-LMA.html */
    .data :
    {
        _start_data = .;
        *(.data*)
        _end_data = .;
    } >sram AT >flash

    .bss :
    {
        _start_bss = .;
        *(.bss*)
        *(COMMON)
        _end_bss = .;
    } >sram

    . = ALIGN(4);

    _start_stack = .;
    /* http://sourceware.org/binutils/docs/ld/MEMORY.html */
    PROVIDE(_end_stack = ORIGIN(sram) + LENGTH(sram));
    /* create startup checksum, UM10800, chapter 3.6.2 */
    PROVIDE(__valid_user_code_checksum = 0 - 
                                         (_end_stack 
                                         + (Reset_Handler + 1) 
                                         + (NMI_Handler + 1) 
                                         + (HardFault_Handler + 1) 
                                         + (MemManage_Handler + 1) 
                                         + (BusFault_Handler + 1) 
                                         + (UsageFault_Handler + 1) 
                                         )
           );
}

_end = .;
