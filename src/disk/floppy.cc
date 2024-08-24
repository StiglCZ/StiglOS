#include "floppy.hh"
#include "../ports.hh"
using namespace System::Ports;

namespace System::Drive {
    void Floppy::InitDMA() {
        outb(0x0a, 0x06);
        outb(0x0c, 0xFF);
        outb(0x04, 0x00);
        outb(0x04, 0x10);
        outb(0x0c, 0xFF);
        outb(0x05, 0xFF);
        outb(0x05, 0x23);
        outb(0x81, 0);
        outb(0x0a, 0x02);
    }
    
    void Floppy::ReadDMA() {
        outb(0x0a, 0x06);
        outb(0x0b, 0x5A);
        outb(0x0a, 0x02);
    }
    
    void Floppy::WriteDMA(){
        outb(0x0a, 0x06);
        outb(0x0b, 0x56);
        outb(0x0a, 0x02);
    }

    
    
};
