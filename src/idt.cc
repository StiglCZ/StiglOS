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
using System::Video::Console;
extern "C" {
    
    void isr(isr_regs* regs) {
        u32 code = regs->int_no;
        isrs[code] = 1;
        if(code <= 20) {       // Exceptions
            conv_number(regs->int_no);
            Console::Write(buffer);
            Console::WriteLine(messages[code]);
            
            Console::WriteLine( "EAX    EBX    ECX    EDX        ESP    EBP");
            conv_number(regs->eax);  Console::Write(buffer); Console::Move(7, -1);
            conv_number(regs->ebx);  Console::Write(buffer); Console::Move(14, -1);
            conv_number(regs->ecx);  Console::Write(buffer); Console::Move(21, -1);
            conv_number(regs->edx);  Console::Write(buffer); Console::Move(32, -1);
            conv_number(regs->esp);  Console::Write(buffer); Console::Move(39, -1);
            conv_number(regs->ebp);  Console::WriteLine(buffer);
            
            Console::WriteLine("DS    ES    FS    GS    SS    CS");
            conv_number(regs->ds);  Console::Write(buffer); Console::Move(6, -1);
            conv_number(regs->es);  Console::Write(buffer); Console::Move(12, -1);
            conv_number(regs->fs);  Console::Write(buffer); Console::Move(18, -1);
            conv_number(regs->gs);  Console::Write(buffer); Console::Move(24, -1);
            conv_number(regs->ss);  Console::Write(buffer); Console::Move(30, -1);
            conv_number(regs->cs);  Console::WriteLine(buffer);
            while(1);
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
