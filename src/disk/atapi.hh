#ifndef _ATAPI
#define _ATAPI
#include "../types.hh"

namespace System::Drive {
    class ATAPI {
        private:
        ATAPI(){}
        const static int SECTOR_SIZE = 2048;
        
        public:
        static u8 diskBuffer[];
        static void ReadSector(u32 sector, bool slave);
    };
}
    
#endif
