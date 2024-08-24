#ifndef _PIT
#define _PIT
#include "../types.hh"

namespace System::Time {
    class PIT {
        enum Ports {
            MAIN0 = 0x40,
            MAIN1 = 0x41,
            MAIN2 = 0x42,
            MCR   = 0x43,
        };
        public:
        static void pit_init(u16 hz);
        static void delay(u32 ms);
    };
};
#endif
