#include "ata.hh"
#include "../ports.hh"
using namespace System::Ports;

namespace System::Drive {
    u8 ATA::diskBuffer[SECTOR_SIZE];
    void ATA::Sync() {
        while ((inb(Ports::COMMAND) & Statuses::BUSY) != 0);
        while ((inb(Ports::COMMAND) & Statuses::DRQ) != 0);
    }
    
    u64 ATA::ReadSize() {
        outb(Ports::DRIVE, 0xA0);
        outb(Ports::COMMAND, 0xEC);
        u8 status = inb(Ports::COMMAND);

        while (status & 0x80)
            status = inb(Ports::COMMAND);

        u16 data[256];
        for (int i = 0; i < 256; ++i) {
            data[i] = inw(Ports::DATA);
        }
        u64 total_sectors =((u64)data[61] << 48) |
            ((u64)data[60]  << 32) |
            ((u64)data[101] << 16)|
            data[100];
        return total_sectors;
    }
    
    void ATA::Select(u32 sector, u8 sect_count) {
        while ((inb(Ports::COMMAND) & Statuses::BUSY) != 0);
        outb(Ports::DRIVE, 0xE0 | ((sector >> 24) & 0x0F));
        outb(Ports::SECTOR_COUNT, sect_count);
        
        outb(Ports::LBA_LOW,  (sector      ) & 0xff);
        outb(Ports::LBA_MID,  (sector >>  8) & 0xff);
        outb(Ports::LBA_HIGH, (sector >> 16) & 0xff);
    }
    
    void ATA::ReadSector(u32 sector) {
        Select(sector, 1);
        outb(Ports::COMMAND, Commands::READ);
        while ((inb(Ports::COMMAND) & Statuses::BUSY) != 0);
        for (int i = 0; i < 256; ++i) {
            u16 word = inw(Ports::DATA);
            diskBuffer[i * 2] = word & 0xFF;
            diskBuffer[i * 2 + 1] = (word >> 8) & 0xFF;
        }
    }

    void ATA::WriteSector(u32 sector) {
        Select(sector, 1);
        outb(Ports::COMMAND, Commands::WRITE);
        for (int i = 0; i < 256; ++i) {
            u16 word = (diskBuffer[i * 2 + 1] << 8) | diskBuffer[i * 2];
            outw(Ports::DATA, word);
        }
        while ((inb(Ports::COMMAND) & Statuses::BUSY) != 0);
    }
}
