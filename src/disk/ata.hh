#ifndef _ATA
#define _ATA
#include "../types.hh"

namespace System::Drive {
    class ATA {
        private:
        ATA(){}
        const static int SECTOR_SIZE = 512;
        static void Select(u32 sector, u8 sect_count);
        
        enum Ports {
            DATA          =0x1F0,
            ERROR         =0x1F1,
            SECTOR_COUNT  =0x1F2,
            DRIVE         =0x1F6,
            COMMAND       =0x1F7,
            LBA_LOW       =0x1F3,
            LBA_MID       =0x1F4,
            LBA_HIGH      =0x1F5,
        };
        
        enum Statuses { 
            DRQ    =0x08,
            BUSY   =0x80,
            READY  =0x40,
        };
        
        enum Commands {
            READ  =0x20,
            WRITE =0x30,
        };
        
        public:
        static u8 diskBuffer[];
        
        static void Sync();
        static u64  ReadSize();

        static void ReadSector(u32 sector);
        static void WriteSector(u32 sector);
    };
}
#endif
