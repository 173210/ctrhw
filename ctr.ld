OUTPUT_FORMAT("elf32-littlearm", "elf32-littlearm", "elf32-littlearm")
OUTPUT_ARCH(arm)

ENTRY(_start)

SECTIONS
{
  . = 0xF1000000;
  .text.start : { *(.text.start ) }
  .text       : { *(.text) }
  .rodata     : { *(.rodata) }
  .data       : { *(.data) }
  .bss        : { *(.bss) }
  . = ALIGN(4);
}
