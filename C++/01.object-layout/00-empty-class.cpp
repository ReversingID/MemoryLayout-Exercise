/*
Identifikasi tata letak memori (memory-layout) sebuah objek.
Setiap objek C++ butuh alokasi di memory untuk menyimpan instance dari data.
Bagaimana jika di class tersebut tidak memiliki isi?

Compile:
    (GCC)  
    $ g++ empty-class.cpp -std=c++11 -o empty-class
    
    (LLVM) 
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
int main()
{
    Example kelas;
    dump_instance("Empty class", kelas);
    return 0;
}

//======== Implementations ==========================================