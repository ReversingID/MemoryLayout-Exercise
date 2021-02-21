/*
    Empty Class (C++)
    Archive of Reversing.ID

Objective:
    Identifikasi tata letak memori (memory-layout) sebuah objek.

    Setiap objek C++ memerlukan alokasi di memory untuk menyimpan instance.
    Bagaimana jika di class tersebut tidak memiliki nilai?

Compile:
    (GCC)  
    $ g++ empty-class.cpp -std=c++11 -o empty-class
    
    (LLVM/Clang) 
    $ clang++ empty-class.cpp -o empty-class

    (MSVC)
    $ cl empty-class.cpp

Run:
    $ empty-class
*/

#include "../util.hpp"

/*
    Amati hasil yang diberikan.

Pertanyaan:
    - Berapa ukuran objek?
    - Jika aplikasi dijalankan berulang-ulang, apakah alamatnya akan sama?
*/

//======== Type Definitions =========================================

class Example { };

//======== Helper Functions =========================================

//======== Main Function ============================================

int main ()
{
    Example kelas;
    dump_instance ("Empty class", kelas);
    return 0;
}

//======== Implementations ==========================================