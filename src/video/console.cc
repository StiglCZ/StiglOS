#include "console.hh"
#include "../ports.hh"
namespace System::Video {
    char Console::Color = 0x07;
    char* const Console::Buffer = (char*)0xB8000;
    int Console::X = 0, Console::Y = 0;
    const int Console::W = 80, Console::H = 25;

    void Console::UpdateCursor(){
        short pos = Y * W + X;
        System::Ports::outb(0x3D4, 0x0F);
        System::Ports::outb(0x3D5, (char) (pos & 0xFF));
        System::Ports::outb(0x3D4, 0x0E);
        System::Ports::outb(0x3D5, (char) ((pos >> 8) & 0xFF));
    }

    void Console::Move(int x, int y) {
        if(x != -1) X = x;
        if(y != -1) Y = y;
    }
    
    void Console::Write(char c) {
        Buffer[(Y * W + X) * 2] = c;
        Buffer[(Y * W + X) * 2 +1] = Color;
        X++;
        UpdateCursor();
    }
    
    void Console::Write(const char* str) {
        while(*str != 0) {
            Write(*str);
            str++;
        }
    }

    void Console::WriteLine(const char* str) {
        Write(str);
        WriteLine();
    }

    void Console::WriteLine() {
        Y++;
        X=0;
    }
    
    void Console::SetChar(int x, int y, char c) {
        Buffer[(y * W + x) * 2] = c;
    }
    
    char Console::GetChar(int x, int y) {
        return Buffer[(y * W + x) * 2];
    }
}
