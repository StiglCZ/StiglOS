#include "pit.hh"
#include "../idt.hh"
#include "../ports.hh"
using namespace System::Ports;

namespace System::Time{
    void PIT::pit_init(u16 hz) {
        outb(Ports::MCR, /*0b00110010*/0x36);
        int divisor = 1193180 / hz;
        outb(Ports::MAIN0, divisor & 0xFF);
        outb(Ports::MAIN0, (divisor >> 8) & 0xFF);
    }
    
    void PIT::delay(u32 ms) {
        u32 target = pit_counter + ms;
        while (pit_counter < target);
    }
}
