#ifndef FLOPPY
#define FLOPPY
#include "../types.hh"

namespace System::Drive {
    class Floppy {
        private:
        static void InitDMA();
        static void ReadDMA();
        static void WriteDMA();
        
        public:
        static void Init();
        static void Read();
        static void Write();
    };
}
#endif

