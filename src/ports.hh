#ifndef PORTS
#define PORTS
#include "types.hh"
namespace System::Ports {
    inline static u8 inb(u16 port) {
        u8 value;
        asm volatile ("inb %1, %0" : "=a"(value) : "Nd"(port));
        return value;
    }
    
    inline static void outb(u16 port, u8 value) {
        asm volatile ("outb %0, %1" : : "a"(value), "Nd"(port));
    }
    
    inline static u16 inw(u16 port) {
        u16 data;
        asm volatile("inw %1, %0" : "=a"(data) : "Nd"(port));
        return data;
    }
    
    inline static void outw(u16 port, u16 data) {
        asm volatile("outw %0, %1" : : "a"(data), "Nd"(port));
    }
    
    inline static void insw(u16 __port, void *__buf, u32 __n) {
        asm volatile("cld; rep; insw" : "+D"(__buf), "+c"(__n) : "d"(__port));
    }
    inline static void outsw(u16 __port, const void *__buf, u32 __n) {
        asm volatile("cld; rep; outsw" : "+S"(__buf), "+c"(__n) : "d"(__port));
    }
}
#endif
