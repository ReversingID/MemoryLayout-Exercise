/*
    Empty Struct (C++)
    Archive of Reversing.ID

Objective:
    Identifikasi tata letak memori (memory-layout) sebuah objek.

    Setiap objek C++ memerlukan alokasi di memory untuk menyimpan instance.
    Apakah struct juga demikian? 
    Bagaimana jika di struct tersebut tidak memiliki isi?

Compile:
    (GCC)  
    $ g++ empty-struct.cpp -std=c++11 -o empty-struct
    
    (LLVM/Clang) 
    $ clang++ empty-struct.cpp -o empty-struct

    (MSVC)
    $ cl empty-struct.cpp

Run:
    $ empty-struct
*/

#include "../util.hpp"

/*
    Amati hasil yang diberikan.

Pertanyaan:
    - Berapa ukuran objek?
    - Jika aplikasi dijalankan berulang-ulang, apakah alamatnya akan sama?
*/

//======== Type Definitions =========================================

struct Example { };

//======== Helper Functions =========================================

//======== Main Function ============================================

int main ()
{
    Example struktur;
    dump_instance ("Empty struct", struktur);
    return 0;
}

//======== Implementations ==========================================