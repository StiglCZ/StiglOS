#include "atapi.hh"
#include "../ports.hh"
using namespace System::Ports;
#define DATA 0
#define ERROR_R 1
#define SECTOR_COUNT 2
#define LBA_LOW 3
#define LBA_MID 4
#define LBA_HIGH 5
#define DRIVE_SELECT 6
#define COMMAND_REGISTER 7
#define CONTROL 0x206

#define ALTERNATE_STATUS 0
namespace System::Drive {
    const u16 port = 0x1F0;
    u8 ATAPI::diskBuffer[SECTOR_SIZE];
    void ata_io_wait(u16 p) {
        inb(p + CONTROL + ALTERNATE_STATUS);
        inb(p + CONTROL + ALTERNATE_STATUS);
        inb(p + CONTROL + ALTERNATE_STATUS);
        inb(p + CONTROL + ALTERNATE_STATUS);
    }
    
    void ATAPI::ReadSector(u32 sector, bool slave) {
        volatile u8 read_cmd[12] = {0xA8, 0,
            (u8)((sector >> 0x18) & 0xFF), (u8)((sector >> 0x10) & 0xFF), (u8)((sector >> 0x08) & 0xFF),
            (u8)((sector >> 0x00) & 0xFF),
            (u8)((1 >> 0x18) & 0xFF),      (u8)((1 >> 0x10) & 0xFF), (u8)((1 >> 0x08) & 0xFF),
            (u8)((1 >> 0x00) & 0xFF), 0, 0
        };

        outb(port + DRIVE_SELECT, 0xA0 & (slave << 4));
        ata_io_wait(port);
        outb(port + ERROR_R, 0x00); 
        outb(port + LBA_MID, 2048 & 0xFF);
        outb(port + LBA_HIGH, 2048 >> 8);
        outb(port + COMMAND_REGISTER, 0xA0);
        ata_io_wait(port);
        
        while (1) {
            u8 status = inb(port + COMMAND_REGISTER);
            if ((status & 0x01) == 1)
                return;
            if (!(status & 0x80) && (status & 0x08))
                break;
            ata_io_wait(port);
        }
        outsw(port + DATA, (u16*)read_cmd, 6);
        
        while (1) {
            u8 status = inb(port + COMMAND_REGISTER);
            if (status & 0x01)
                return;
            if (!(status & 0x80) && (status & 0x08))
                break;
        }

		int size = inb(port + LBA_HIGH) << 8 | inb(port + LBA_MID);

		insw(port + DATA, (u16 *) ((u8*) diskBuffer), size / 2);


    }
}
