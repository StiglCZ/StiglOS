#ifndef _RTC
#define _RTC
#include "../types.hh"
namespace System::Time {
    struct Time {
        u8 seconds;
        u8 minutes;
        u8 hours;
        
        u8 day;
        u8 month;
        u8 year;
        u8 century;
    };
    
    class RTC {
        private:
        enum Ports {
            MAIN = 0x70,
            DATA = 0x71,
        };
        enum Statuses{
            A = 0x0A,
            B = 0x0B,
        };
        enum Periods {
            SECONDS = 0x00,
            MINUTES = 0x02,
            HOURS   = 0x04,
            WEEKDAY = 0x06,
            DAY     = 0x07,
            MONTH   = 0x08,
            YEAR    = 0x09,
            CENTURY = 0x32
        };
        static u8 ReadRegister(u8 reg);
        static u8 BCDtoBinary(u8 bin);
        public:
        static Time GetTime();
        static void GetTime(Time& time);
        
    };
}
#endif
