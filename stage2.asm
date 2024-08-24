[bits 32]
extern main
[global _start]
[extern setup_idt]
[extern setup_pic]
[extern setup_irq]
_start:
    mov eax, 0
    mov ebx, 0
    mov ecx, 0
    mov edx, 0
    mov esi, 0
    mov edi, 0
    
    mov esp, 0x9000
    mov ebp, esp

    cli
    call setup_idt
    call setup_pic
    call setup_irq
    sti
    
    call main
