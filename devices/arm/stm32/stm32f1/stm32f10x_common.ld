ENTRY(Reset_Handler)

/* begin of stack in ARM adresses are decreasing */
_estack = ORIGIN(RAM) + LENGTH(RAM);

/* Place sections in memory */
SECTIONS
{
    /* startup code */
    .isr_vector :
    {
        . = ALIGN(4);
        __isr_vector_start__ = .;
        KEEP(*(.isr_vector))
        ASSERT(. != __isr_vector_start__, ".isr_vector section is empty! Startup code must be provided");
        . = ALIGN(4);
    } >FLASH

    /* user code & read only data */
    .text :
    {
        . = ALIGN(4);
        _stext = .;
        *(.text)
        *(.text*)
        *(.glue_7)
        *(.glue_7t)
        *(.eh_frame)
        KEEP(*(.init)) /* static constructors */
        KEEP(*(.fini)) /* static destructors */
        . = ALIGN(4);
        _etext = .;
    } >FLASH

    .rodata :
    {
        . = ALIGN(4);
        *(.rodata)
        *(.rodata*)
        . = ALIGN(4);
    } >FLASH

    /* ARM stack unwinding */
    .ARM.extab :
    {
        *(.ARM.extab*)
    } >FLASH
    .ARM.exidx :
    {
        *(.ARM.exidx*)
    } >FLASH

    /* Newlib C++ support */
    .preinit_array :
    {
        PROVIDE_HIDDEN(__preinit_array_start = .);
        KEEP(*(.preinit_array*))
        PROVIDE_HIDDEN(__preinit_array_end = .);
    } >FLASH
    .init_array :
    {
        PROVIDE_HIDDEN(__init_array_start = .);
        KEEP(*(SORT(.init_array.*)))
        KEEP(*(.init_array*))
        PROVIDE_HIDDEN(__init_array_end = .);
    } >FLASH
    .fini_array :
    {
        PROVIDE_HIDDEN(__fini_array_start = .);
        KEEP(*(SORT(.fini_array.*)))
        KEEP(*(.fini_array*))
        PROVIDE_HIDDEN(__fini_array_end = .);
    } >FLASH

    _sidata = LOADADDR(.data);
    .data :
    {
        . = ALIGN(4);
        _sdata = .;
        *(.data)
        *(.data*)
        . = ALIGN(4);
        _edata = .;
    } >RAM AT> FLASH

    . = ALIGN(4);
    .bss :
    {
        _sbss = .;
        __bss_start__ = _sbss;
        *(.bss)
        *(.bss*)
        *(COMMON)
        . = ALIGN(4);
        _ebss = .;
        __bss_end__ = _ebss;
    } >RAM

    ._heap :
    {
        . = ALIGN(4);
        . = . + _heap_size;
        . = ALIGN(4);
    } >RAM
    ._stack :
    {
        . = ALIGN(4);
        . = . + _stack_size;
        . = ALIGN(4);
    } >RAM

    /DISCARD/ :
    {
        libc.a ( * )
        libm.a ( * )
        libgcc.a ( * )
    }
}

__isr_vector_size__ = SIZEOF(.isr_vector);
__text_size__ = SIZEOF(.text);
__data_size__ = SIZEOF(.data);
__bss_size__ = SIZEOF(.bss);
