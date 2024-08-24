#include "idt.hh"
#include "ports.hh"
#include "video/console.hh"
using namespace System::Ports;

int key;
u8 isrs[64];
u32 pit_counter = 0;

static char messages[][32] = {
    "Divide By Zero\0",
    "Debug\0",
    "Non-Maskable Interrupt\0",
    "Breakpoint\0",
    "Overflow\0",
    "Bound Range Exceeded\0",
    "Invalid OpCode\n",
    "Device Not Available\0",
    "Double Fault\0",
    "Coprocessor Segment Overrun\0",
    "Invalid TTS\0",
    "Segment Not Present\0",
    "Stack Segment Fault\0",
    "General Protection Fault\0",
    "Page Fault\0",
    "x87 Floating-Point Exception\0",
    "Alignment Check\0",
    "Machine Check\0",
    "SIMD Floating Point Exception\0",
    "Virtualization Exception\0",
    "Security Exception\0"
};
char buffer[32];
void conv_number(int num) {
    int counter = 0;
    if(num <  0) {buffer[counter++] = 45; num *= -1;}
    if(num == 0) buffer[counter++] = 48;
    int start = counter;
    while(num > 0) {
        char digit = num % 10;
        buffer[counter++] = digit + 48;
        num -= digit;
        num /= 10;
    }
    int end = counter-1;
    for(int i =0; i < (end - start / 2); i++){
        int tmp = buffer[start + i];
        buffer[start + i] = buffer[end - i];
        buffer[end - i] = tmp;
    }
    buffer[counter] = 0;
}
extern "C" {
    
    void isr(isr_regs* regs) {
        u32 code = regs->int_no;
        isrs[code] = 1;
        if(code <= 20) {       // Exceptions
            System::Video::Console::WriteLine(messages[code]);
            System::Video::Console::Write(" EAX = "); conv_number(regs->eax);    System::Video::Console::Write(buffer);
            System::Video::Console::Write(" EBX = "); conv_number(regs->ebx);    System::Video::Console::Write(buffer);
            System::Video::Console::Write(" ECX = "); conv_number(regs->ecx);    System::Video::Console::Write(buffer);
            System::Video::Console::Write(" EDX = "); conv_number(regs->edx);    System::Video::Console::Write(buffer);
            System::Video::Console::Write(" ESP = "); conv_number(regs->esp);    System::Video::Console::Write(buffer);
            System::Video::Console::Write(" EBP = "); conv_number(regs->ebp);    System::Video::Console::Write(buffer);
            System::Video::Console::Write(" INT = "); conv_number(regs->int_no); System::Video::Console::Write(buffer);
            System::Video::Console::WriteLine();
            System::Video::Console::Write("DS  = "); conv_number(regs->ds);     System::Video::Console::WriteLine(buffer);
            System::Video::Console::Write("ES  = "); conv_number(regs->es);     System::Video::Console::WriteLine(buffer);
            System::Video::Console::Write("FS  = "); conv_number(regs->fs);     System::Video::Console::WriteLine(buffer);
            System::Video::Console::Write("GS  = "); conv_number(regs->gs);     System::Video::Console::WriteLine(buffer);
            System::Video::Console::Write("SS  = "); conv_number(regs->ss);     System::Video::Console::WriteLine(buffer);
            System::Video::Console::WriteLine();
            System::Video::Console::Write("CS:IP = "); conv_number(regs->cs);   System::Video::Console::Write(buffer);
            System::Video::Console::Write(":"); conv_number(regs->eip);         System::Video::Console::WriteLine(buffer);
        } else if(code < 32) { // Custom
        } else {               // IRQ
            switch(code) {
                case 0x20:     // PIT    
                    pit_counter++;
                    break;
                case 0x21:
                    inb(0x60);
                    break;
            }
        }
        outb(0x20, 0x20);
    }
}
