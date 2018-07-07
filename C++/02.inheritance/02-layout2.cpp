/*
Identifikasi tata letak memori (memory-layout) sebuah objek.
Jika sebuah class diturunkan dari class lain, bagaimana ia dibangun?

Compile:
    (GCC)  
    $ g++ layout2.cpp -std=c++11 -o layout2
    
    (LLVM) 
    $ clang++ layout2.cpp -o layout2

    (MSVC)
    $ cl layout2.cpp

Run:
    $ layout2
*/
#include "../util.hpp"

/*
Amati masing-masing alamat yang ditampilkan.
Pertanyaan:
    - Apabila suatu class memiliki beberapa class lain sebagai anggota,
      bagaimana layout dari setiap objek di memory?

Kesimpulan:
    Ketika instansiasi sebuah class dengan dua atau lebih base, class turunan 
    akan mewarisi data dari seluruh base dengan diletakkan berdampingan 
    sesuai urutan deklarasi.
*/

//======== Type Definitions =========================================
struct Base1
{
    uint32_t x, y;

    Base1() 
    {
        x = 135;
        y = 182;
    }
};

struct Base2
{
    uint32_t z;

    Base2()
    {
        z = 234;
    }
};

/*
class Derivate diturunkan dari Base1 dan Base2
class akan memiliki data dengan urutan:
    - warisan dari Base1
    - warisan dari Base2
    - data class Derivate
*/
struct Derivate : public Base1, public Base2 
{
    uint32_t w;

    void printVars()
    {
        printf("Location w: [%p]\n", &w);
        printf("Location x: [%p]\n", &x);
        printf("Location y: [%p]\n", &y);
        printf("Location z: [%p]\n", &z);
    }
};

//======== Helper Functions =========================================

//======== Main Function ============================================
int main()
{
    printf("[+] Spawn derivate...\n");
    Derivate derivate;
    
    printf("Size of derivate: %d\n", sizeof(Derivate));
    printf("Size of Base1: %d\n", sizeof(Base1));
    printf("Size of Base2: %d\n", sizeof(Base2));
    derivate.printVars();

    return 0;
}

//======== Implementations ==========================================