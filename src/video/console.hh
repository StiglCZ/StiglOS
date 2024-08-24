#ifndef CONSOLE
#define CONSOLE

namespace System::Video {
    class Console {
        private:
        const static int W, H;
        static int X, Y;
        Console();
        static void UpdateCursor();
        
        public:
        static char Color;
        static char* const Buffer;
        
        static void Write(char c);
        static void Write(const char* str);
        static void WriteLine(const char* str);
        static void WriteLine();
        
        static void SetChar(int x, int y, char c);
        static char GetChar(int x, int y);
        
        static void ReadKey(bool intercept);
        static void ReadLine();
        
        static void Move(int x, int y);
    };
    
};
#endif
