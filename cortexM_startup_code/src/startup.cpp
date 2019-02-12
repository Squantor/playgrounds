/*
 * Unified Cortex Startup - C startup file
 *
 * This file is in public domain
 *
 * Put together by Paul Sokolovsky based on article by Vanya Sergeev
 * http://dev.frozeneskimo.com/notes/cortex_cmsis/ , GNU ld documentation
 * and numerous other public resources.
 *
 */

#include <stdint.h>

/* Declare linker-defined symbols. The only thing of interest
   regarding these symbols is their *address*. uint32_t hints
   of alignment. */
extern uint32_t _data_flash;
extern uint32_t _start_data;
extern uint32_t _end_data;
extern uint32_t _start_bss;
extern uint32_t _end_bss;

/* C main function */
extern int main(void);
/* standard interrupt/exception handler, best replace this by an assert?*/
void Dummy_Handler(void);
/* prototypes used by the ARM ISR vector table */
void Reset_Handler(void);

#include <cortexm_irqs.c>
#include <mcu_irq.c>

/* Based on http://sourceware.org/binutils/docs/ld/Output-Section-LMA.html */
void Reset_Handler(void) {
    register uint32_t *src, *dst;

    /* Copy data section from flash to RAM */
    src = &_data_flash;
    dst = &_start_data;
    while (dst < &_end_data)
        *dst++ = *src++;

    /* Clear the bss section, assumes .bss goes directly after .data */
    dst = &_start_bss;
    while (dst < &_end_bss)
        *dst++ = 0;

    main();
    while (1);
}

void Dummy_Handler(void) {
    /* Receiving an unexpected interrupt is considered a bug
       in the program. Let's make it very visible by just
       hanging the processing. Ignoring it by just returning
       may result in very complicated debugging sessions. */
    while (1);
}
