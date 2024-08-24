[bits 32]
extern main
[global _start]
[extern setup_idt]
[extern setup_pic]
[extern setup_irq]
_start:
    mov esp, 0x10000
    mov ebp, esp

    cli
    call setup_idt
    call setup_pic
    call setup_irq
    sti
    
    call main
