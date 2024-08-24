#include "vga.hh"

namespace System::Video {
    u8* const FrameBuffer::Buffer = (u8*)0xA0000;
    
    void FrameBuffer::DrawPixel(int x, int y, u8 c) {
        Buffer[x + y * W] = c;
    }
    u8 FrameBuffer::GetPixel(int x, int y) {
        return Buffer[x + y * W];
    }
    
}
