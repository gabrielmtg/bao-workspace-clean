ENTRY(_start)

SECTIONS
{   
    .nloader : {
        KEEP(*(.nloader))
    }

    .linux 0x200000 : { 
        __linux_start = .;
        KEEP(*(.linux)) 
        __linux_end = .;
    }  

    .dtb 0x3500000 : ALIGN(8) { 
        __dtb_start = ABSOLUTE(.);
        KEEP(*(.dtb)) 
        __dtb_end = .;
    }  

    .initrd 0x4000000 : ALIGN(8) { 
        __initrd_start = ABSOLUTE(.);
        KEEP(*(.initrd)) 
        __initrd_end = .;
    }  
}
