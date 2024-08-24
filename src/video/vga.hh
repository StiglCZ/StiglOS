#ifndef VGA
#define VGA
#include "../types.hh"
namespace System::Video {
    class FrameBuffer {
        private:
        const static int W = 320, H = 200;
        public:
        static u8* const Buffer;

        static void DrawPixel(int x, int y, u8 color);
        static u8 GetPixel(int x, int y);
    };
};


#endif
