[org 0x7c00]
[bits 16]
global start
start:
    mov [bootd], dl
segments:
    mov ax, 0
    mov ds, ax
    mov es, ax
    mov fs, ax
    mov gs, ax
    mov ss, ax
stack:
    mov sp, 0x7c00
    mov bp, sp
disk:
    mov ax, 0x0220
    mov bx, 0x7e00
    mov cx, 0x0002
    mov dl, [bootd]
    mov dh, 0
    int 13h
    jc drive_error
video:
    mov ax, 0x03
    int 10h
a20:
    cli
    in al, 0x92
    or al, 0x02
    out 0x92, al
mode32:
    lgdt [gdtr]
    mov eax, cr0
    or eax, 1
    mov cr0, eax
    jmp CODE_SEG:start32

drive_error:
    mov si, errmsg
    mov ah, 0x0e
drive_error_loop:
    mov al, [si]
    inc si
    
    int 10h
    cmp al, 0
    jne drive_error_loop
    jmp $

CODE_SEG equ code - gdt_start
DATA_SEG equ data - gdt_start
gdt_start:
null: dq 0x0000000000000000
code: dq 0x00CF9A0000000080;FFFF (instead of 0x0080)
data: dq 0x00CF920000000080;FFFF (instead of 0x0080)
gdtr:
    dw gdtr - gdt_start - 1
    dd gdt_start
errmsg:  db 'Drive error', 0
bootd:   db 0

[bits 32]
start32:
    mov ax, DATA_SEG
    mov ds, ax
    mov es, ax
    mov fs, ax
    mov gs, ax
    mov ss, ax
    
    jmp 0x7e00
    
    times 510-($-$$) db 0
    dw 0xAA55
