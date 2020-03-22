ENTRY(Reset_Handler)

/* begin of stack in ARM adresses are decreasing */
_estack = ORIGIN(RAM) + LENGTH(RAM);

_fs_flash_start = ORIGIN(FS_FLASH);
_fs_flash_end = ORIGIN(FS_FLASH) + LENGTH(FS_FLASH);

_kernel_ram_start = ORIGIN(KERNEL_RAM);
_kernel_ram_end = ORIGIN(KERNEL_RAM) + LENGTH(KERNEL_RAM);

/* Place sections in memory */
SECTIONS
{
    /* startup code */
    .isr_vector :
    {
        . = ALIGN(4);
        KEEP(*(.isr_vector))
        . = ALIGN(4);
    } >FLASH

    /* user code */
    .text :
    {
        . = ALIGN(4);
        _stext = .;
        *(.text)
        *(.text*)
        *(.glue_7)
        *(.glue_7t)
        *(.eh_frame)
        KEEP (*(.init))
        KEEP (*(.fini))
        . = ALIGN(4);
        _etext = .;
    } >FLASH

    /* read only data */
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
        KEEP(*(.fini_array*))
        KEEP(*(SORT(.fini_array.*)))
        PROVIDE_HIDDEN(__fini_array_end = .);
    } >FLASH

    _sidata = .;
    .data : AT ( _sidata )
    {
        . = ALIGN(4);
        _sdata = .;
        *(.data)
        *(.data*)
        . = ALIGN(4);
        _edata = .;
    } >RAM

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

    PROVIDE ( end = _ebss );
    PROVIDE ( _end = _ebss );
    /* Test that stack and heap will fit in memory */
    ._heap_stack :
    {
        . = ALIGN(4);
        __heap_start = .;
        . = . + _heap_size;
        __heap_end = .;
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
