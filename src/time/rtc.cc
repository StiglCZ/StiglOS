#include "rtc.hh"
#include "../ports.hh"
using namespace System::Ports;

namespace System::Time {
    u8 RTC::ReadRegister(u8 reg) {
        outb(Ports::MAIN, reg);
        return inb(Ports::DATA);
    }
    
    u8 RTC::BCDtoBinary(u8 bcd_value) {
        return (bcd_value >> 4) * 10 + (bcd_value & 0x0F);
    }
    void RTC::GetTime(struct Time& time) {
        time.century = BCDtoBinary(ReadRegister(Periods::CENTURY));
        time.seconds = BCDtoBinary(ReadRegister(Periods::SECONDS));
        time.minutes = BCDtoBinary(ReadRegister(Periods::MINUTES));
        time.hours   = BCDtoBinary(ReadRegister(Periods::HOURS));
        time.day     = BCDtoBinary(ReadRegister(Periods::DAY  ));
        time.month   = BCDtoBinary(ReadRegister(Periods::MONTH));
        time.year    = BCDtoBinary(ReadRegister(Periods::YEAR));
    }
    Time RTC::GetTime() {
        Time time;
        GetTime(time);
        return time;
    }
};
