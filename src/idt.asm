[bits 32]
section .text
PIC1P EQU 0x20                  ; PIC ports
PIC1S EQU 0x21
PIC2P EQU 0xA0
PIC2S EQU 0xA1

global setup_idt
global setup_pic
global setup_irq

extern isr   
setup_idt:
    lidt [idtr]
    ret
    
setup_pic:                      ; Programmable interupt controler
    mov cx, PIC1P
    mov dx, PIC2P
    
    mov al, 0x11
    out PIC1P, al
    out PIC2P, al
    
    mov al, 0x04
    out PIC1S, al
    mov al, 0x02
    out PIC2S, al

    mov al, 0x01
    out PIC1S, al
    out PIC2S, al
    ret
    
setup_irq:
    mov al, 0xff
    out PIC1S, al
    out PIC2S, al
    ret
    
isr0:                           ; Divide By Zero
    cli
    push word 0
    jmp handler

isr1:                           ; Debug
    cli
    push word 1
    jmp handler

isr2:                           ; Non-Maskable Interrupt
    cli
    push word 2
    jmp handler

isr3:                           ; Breakpoint
    cli
    push word 3
    jmp handler

isr4:                           ; Overflow
    cli
    push word 4
    jmp handler

isr5:                           ; Bound Range Exceeded
    cli
    push word 5
    jmp handler

isr6:                           ; Invalid OpCode
    cli
    push word 6
    jmp handler

isr7:                           ; Device Not Available
    cli
    push word 7
    jmp handler

isr8:                           ; Double Fault
    cli
    push word 8
    jmp handler

isr9:                           ; Coprocessor Segment Overrun
    cli
    push word 9
    jmp handler

isr10:                          ; Invalid TTS
    cli
    push word 10
    jmp handler

isr11:                          ; Segment Not Present
    cli
    push word 11
    jmp handler

isr12:                          ; Stack Segment Fault
    cli
    push word 12
    jmp handler

isr13:                          ; General Protection Fault
    cli
    push word 13
    jmp handler

isr14:                          ; Page Fault
    cli
    push word 14
    jmp handler

isr15:                          ; x87 Floating-Point Exception
    cli
    push word 15
    jmp handler

isr16:                          ; Alignment Check
    cli
    push word 16
    jmp handler

isr17:                          ; Machine Check
    cli
    push word 17
    jmp handler

isr18:                          ; SIMD Floating Point Exception
    cli
    push word 18
    jmp handler

isr19:                          ; Virtualization Exception
    cli
    push word 19
    jmp handler

isr20:                          ; Security Exception
    cli
    push word 20
    jmp handler
isr21:                          ; Customs
    jmp $
isr22:
    jmp $
isr23:
    jmp $
isr24:
    jmp $
isr25:
    jmp $
isr26:
    jmp $
isr27:
    jmp $
isr28:
    jmp $
isr29:
    jmp $
isr30:
    jmp $
isr31:
    jmp $
isr32:                          ; Programmable Interrupt Timer
    cli
    push word 32
    jmp handler
isr33:                          ; Keyboard
    cli
    push word 33
    jmp handler

isr34:                          ; Used Internally
    cli
    push word 34
    jmp handler

isr35:                          ; COM2
    cli
    push word 35
    jmp handler

isr36:                          ; COM1
    cli
    push word 36
    jmp handler

isr37:                          ; LPT2
    cli
    push word 37
    jmp handler

isr38:                          ; Floppy disk
    cli
    push word 38
    jmp handler

isr39:                          ; LPT1
    cli
    push word 39
    jmp handler

isr40:                          ; CMOS RTC
    cli
    push word 40
    jmp handler

isr41:                          ; Peripherals
    cli
    push word 41
    jmp handler

isr42:                          ; Peripherals
    cli
    push word 42
    jmp handler

isr43:                          ; Peripherals
    cli
    push word 43
    jmp handler

isr44:                          ; PS/2 Mouse
    cli
    push word 44
    jmp handler

isr45:                          ; FPU / Coprocessor / Inter-processor
    cli
    push word 45
    jmp handler

isr46:                          ; Primary ATA Hard Disk
    cli
    push word 46
    jmp handler

isr47:                          ; Secondary ATA Hard Disk
    cli
    push word 47
    jmp handler
handler:                        ; Error code in stack    
    pusha
    push ds
    push es
    push fs
    push gs

    mov ax, 0x10
    mov ds, ax
    mov es, ax
    mov fs, ax
    mov gs, ax
    
    mov eax, esp
    push eax
    
    mov eax, isr
    call eax

    pop eax
    pop gs
    pop fs
    pop es
    pop ds
    popa

    add esp, 8
    
    sti
    iret
    
section .data
idt:                            ; Interupt descriptor table
    dw isr0,  8, 0x8e00, 0x0000
    dw isr1,  8, 0x8e00, 0x0000
    dw isr2,  8, 0x8e00, 0x0000
    dw isr3,  8, 0x8e00, 0x0000
    dw isr4,  8, 0x8e00, 0x0000
    dw isr5,  8, 0x8e00, 0x0000
    dw isr6,  8, 0x8e00, 0x0000
    dw isr7,  8, 0x8e00, 0x0000
    dw isr8,  8, 0x8e00, 0x0000
    dw isr9,  8, 0x8e00, 0x0000
    dw isr10, 8, 0x8e00, 0x0000
    dw isr11, 8, 0x8e00, 0x0000
    dw isr12, 8, 0x8e00, 0x0000
    dw isr13, 8, 0x8e00, 0x0000
    dw isr14, 8, 0x8e00, 0x0000
    dw isr15, 8, 0x8e00, 0x0000
    dw isr16, 8, 0x8e00, 0x0000
    dw isr17, 8, 0x8e00, 0x0000
    dw isr18, 8, 0x8e00, 0x0000
    dw isr19, 8, 0x8e00, 0x0000
    dw isr20, 8, 0x8e00, 0x0000
    
    dw isr21, 8, 0x0000, 0x0000
    dw isr22, 8, 0x0000, 0x0000
    dw isr23, 8, 0x0000, 0x0000
    dw isr24, 8, 0x0000, 0x0000
    dw isr25, 8, 0x0000, 0x0000
    dw isr26, 8, 0x0000, 0x0000
    dw isr27, 8, 0x0000, 0x0000
    dw isr28, 8, 0x0000, 0x0000
    dw isr29, 8, 0x0000, 0x0000
    dw isr30, 8, 0x0000, 0x0000
    dw isr31, 8, 0x0000, 0x0000
    
    dw isr32, 8, 0x8e00, 0x0000
    dw isr33, 8, 0x8e00, 0x0000
    dw isr34, 8, 0x8e00, 0x0000
    dw isr35, 8, 0x8e00, 0x0000
    dw isr36, 8, 0x8e00, 0x0000
    dw isr37, 8, 0x8e00, 0x0000
    dw isr38, 8, 0x8e00, 0x0000
    dw isr39, 8, 0x8e00, 0x0000
    dw isr40, 8, 0x8e00, 0x0000
    dw isr41, 8, 0x8e00, 0x0000
    dw isr42, 8, 0x8e00, 0x0000
    dw isr43, 8, 0x8e00, 0x0000
    dw isr44, 8, 0x8e00, 0x0000
    dw isr45, 8, 0x8e00, 0x0000
    dw isr46, 8, 0x8e00, 0x0000
    dw isr47, 8, 0x8e00, 0x0000
idtr:
    idt_size :  dw idtr - idt
    idt_base :  dd idt
