#ifndef IDT
#define IDT
#include "types.hh"
extern "C" {
    typedef struct isr_regs{
        u32 gs, fs, es, ds;
        u32 edi, esi, ebp, esp, ebx, edx, ecx, eax;
        u32 int_no, err_code;
        u32 eip, cs, eflags, useresp, ss;
    } __attribute__ ((packed)) regs;
    extern void setup_idt();
    extern void setup_pic();
    extern void irqs();
    extern void isr(isr_regs* regs);
}
extern u8 isrs[];
extern u8 keyboard[];
extern u32 pit_counter;
inline void wait_irq(int irq) {
    while(!isrs[irq]);
    isrs[irq] = 0;
}
#endif
