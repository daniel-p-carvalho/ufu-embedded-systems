/****************************************************************************
 * startup.c
 *
 * Description:
 * This file contains the entry point for the ARM Cortex-M4 processor. It
 * provides the minimal hardware initialization (Reset Handler) necessary
 * to prepare the C runtime environment (CRT) before executing the main
 * application.
 *
 * Target: 
 * STM32L432 (ARM Cortex-M4) - Universidade Federal de Uberlândia
 *
 * Author: Daniel Pereira de Carvalho <daniel.carvalho@ufu.br>
 * Copyright (C) 2026 Daniel Pereira de Carvalho. All rights reserved.
 *
 ****************************************************************************/

/****************************************************************************
 * Included Files
 ****************************************************************************/

#include <stdint.h>

/****************************************************************************
 * Pre-processor Definitions
 ****************************************************************************/

/* ASSIGNMENT: Move the Stack Pointer initialization to the Linker Script.
 *
 * DISCUSSION: Currently, the initial Stack Pointer (STACK_START) is defined
 *   using a hardcoded macro based on SRAM_END. While this works for a
 *   specific device, a more robust approach in professional embedded systems
 *   is to import this address from the Linker Script using an external symbol.
 *
 *   Your task is to:
 *   1. Remove the SRAM_START, SRAM_SIZE, and STACK_START macros below.
 *   2. Declare an external symbol: extern uint32_t _estack_addr;
 *   3. Update the first entry of the vector table to use (uint32_t)&_estack_addr.
 *
 * TECHNICAL NOTE: The ARM Cortex-M architecture requires the Stack Pointer 
 *   to be aligned to an 8-byte boundary at all times to comply with the 
 *   Procedure Call Standard for the ARM Architecture (AAPCS). In your Linker
 *   Script, ensure the symbol is defined after an ALIGN(8) directive 
 *   at the very end of the RAM section.
 ****************************************************************************/

#define SRAM_START  0x20000000U
#define SRAM_SIZE   (128U * 1024U)
#define SRAM_END    ((SRAM_START) + (SRAM_SIZE))

#define STACK_START SRAM_END

/****************************************************************************
 * Private Function Prototypes
 ****************************************************************************/

/* If compiling as C++ ensure symbols use C linkage */
#ifdef __cplusplus
extern "C" {
#endif

int main(void);

void reset_handler     (void);
void nmi_handler       (void) __attribute__ ((weak, alias("default_handler")));
void hardfault_handler (void) __attribute__ ((weak, alias("default_handler")));
void memmanage_handler (void) __attribute__ ((weak, alias("default_handler")));
void busfault_handler  (void) __attribute__ ((weak, alias("default_handler")));
void usagefault_handler(void) __attribute__ ((weak, alias("default_handler")));
void svc_handler       (void) __attribute__ ((weak, alias("default_handler")));
void debugmon_handler  (void) __attribute__ ((weak, alias("default_handler")));
void pendsv_handler    (void) __attribute__ ((weak, alias("default_handler")));
void systick_handler   (void) __attribute__ ((weak, alias("default_handler")));

#ifdef __cplusplus
}
#endif

/****************************************************************************
 * Linker-provided symbols
 ****************************************************************************/

/* The reset handler uses these symbols to copy initialized data from FLASH
 * to RAM and to zero the .bss area.
 *  _sdata - start address of .data in RAM
 *  _edata - end address of .data in RAM
 *  _la_data - load address of .data in FLASH (where initialized values live)
 *  _sbss - start of .bss in RAM
 *  _ebss - end of .bss in RAM
 */
extern uint32_t _sdata;
extern uint32_t _edata;
extern uint32_t _la_data;
extern uint32_t _sbss;
extern uint32_t _ebss;

/****************************************************************************
 * Vector Table
 *
 * The vector table must be placed at the start of flash (or at the address
 * pointed by the VTOR). The first entry is the initial stack pointer value,
 * followed by the addresses of exception/interrupt handlers. The section
 * attribute places the table in the .isr_vector section so the linker script
 * can locate it at the correct flash address. The array is declared const
 * and marked used/aligned to prevent removal/relocation.
 *
 * ASSIGNMENT: Complete the vector table for the STM32L432 microcontroller.
 *
 * DISCUSSION: The table below currently contains only the System Exceptions
 *   (the first 16 entries defined by the ARM Cortex-M4 core). To make the
 *   microcontroller fully functional for peripheral interaction, you must
 *   add the External Interrupts (IRQs) specific to the STM32L432.
 *
 *   Refer to the "Interrupt and exception vectors" table in the STM32L432 
 *   Reference Manual (RM0394). You should add at least the entries for 
 *   WWDG_IRQHandler, PVD_PVM_IRQHandler, and TAMP_STAMP_IRQHandler to 
 *   start the peripheral interrupt list.
 *
 * TECHNICAL NOTE: Remember that external interrupts start at offset
 *   0x0000 0040. Each entry must be a 4-byte address. If a handler is not
 *   yet implemented, you can use a default_handler or a weak alias.
 ****************************************************************************/
__attribute__((section(".isr_vector"), used, aligned(4)))
const vector_table_entry vectors[] =
{
  STACK_START,                  /* 0x0000 0000: Initial SP */
  (uint32_t)reset_handler,      /* 0x0000 0004: Reset */
  (uint32_t)nmi_handler,        /* 0x0000 0008: NMI */
  (uint32_t)hardfault_handler,  /* 0x0000 000C: HardFault */
  (uint32_t)memmanage_handler,  /* 0x0000 0010: MemManage */
  (uint32_t)busfault_handler,   /* 0x0000 0014: BusFault */
  (uint32_t)usagefault_handler, /* 0x0000 0018: UsageFault */
  0,                            /* 0x0000 001C: Reserved */
  0,                            /* 0x0000 0020: Reserved */
  0,                            /* 0x0000 0024: Reserved */
  0,                            /* 0x0000 0028: Reserved */
  (uint32_t)svc_handler,        /* 0x0000 002C: SVCall */
  (uint32_t)debugmon_handler,   /* 0x0000 0030: Debug Monitor */
  0,                            /* 0x0000 0034: Reserved */
  (uint32_t)pendsv_handler,     /* 0x0000 0038: PendSV */
  (uint32_t)systick_handler,    /* 0x0000 003C: SysTick */

  /* External Interrupts (IRQs) start here */
  /* TODO: Add STM32L432 specific interrupt handlers according to RM0394 */
};

/****************************************************************************
 * Name: reset_handler
 *
 * This function runs immediately after reset. For bare-metal C programs that
 * don't use dynamic init, constructors or stdio. It only needs to copy the
 * .data section initial values from FLASH to RAM, zero-initialize the .bss
 * section then call main().
 *
 * The linker script must provide the _sdata, _edata, _la_data, _sbss, _ebss
 * symbols. After calling main(), this implementation loops forever if main()
 * returns.
 *
 * Params:
 *
 * Return:
 *
 ****************************************************************************/
void reset_handler(void)
{
  /* ASSIGNMENT: Modify the code below to perform initialization using 32-bit
   *   blocks (uint32_t)
   *
   * DISCUSSION: Currently, the code uses 8-bit blocks (uint8_t). While this
   *   works regardless of memory alignment, it is highly inefficient. Since
   *   the ARM Cortex-M4 has a 32-bit data bus, an 8-bit copy requires 4
   *   individual memory access cycles to move the same amount of data that
   *   a 32-bit copy would handle in a single cycle.
   *
   * TECHNICAL NOTE: Switching to 32-bit blocks requires that all section
   *   symbols (_sdata, _edata, _sbss, etc.) be aligned to 4-byte boundaries
   *   in the Linker Script using the ALIGN(4) directive. Failure to do so may
   *   result in a UsageFault exception due to unaligned memory access.
   */

  /* Copy initialized data from FLASH (_la_data) to RAM (_sdata.._edata) using
   * 8-bit blocks
   */
  uint8_t *p_dst = (uint8_t *)&_sdata;
  uint8_t *p_src = (uint8_t *)&_la_data;
  while (p_dst < (uint8_t *)&_edata)
    {
      *p_dst++ = *p_src++;
    }

  /* Zero-fill the .bss section (_sbss.._ebss) using 8-bit blocks */
  p_dst = (uint8_t *)&_sbss;
  while (p_dst < (uint8_t *)&_ebss)
    {
      *p_dst++ = 0;
    }

  /* Call the application's entry point */
  main();

  /* Ensure this function does not return. If main returns, loops forever */
  while(1){};
}

/****************************************************************************
 * Name: default_handler
 *
 * A simple infinite-loop handler used as the weak default for exceptions and
 * interrupts that the application does not implement. During development it
 * is useful to place a breakpoint here to detect unexpected interrupts.
 *
 * Params:
 *
 * Return:
 *
 ****************************************************************************/
void default_handler(void)
{
  while(1){};
}