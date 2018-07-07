/*
Identifikasi tata letak memori (memory-layout) sebuah objek.
Jika sebuah class diturunkan dari class lain, bagaimana ia direpresentasikan?

Compile:
    (GCC)  
    $ g++ layout.cpp -std=c++11 -o layout
    
    (LLVM) 
    $ clang++ layout.cpp -o layout

    (MSVC)
    $ cl layout.cpp

Run:
    $ layout
*/
#include "../util.hpp"

/*
Amati masing-masing alamat yang ditampilkan.
Pertanyaan:
    - Apabila suatu class memiliki beberapa class lain sebagai anggota,
      bagaimana layout dari setiap objek di memory?

Kesimpulan: 
    Sebuah class diturunkan dari class lain akan mewarisi data yang diletakkan
    berdampingan dengan data yang ia miliki.
*/

//======== Type Definitions =========================================
struct Base
{
    uint32_t x, y, z;

    Base() 
    {
        x = 135;
        y = 182;
    }
    void printVars()
    {
        printf("Location x: [%p]\n", &x);
        printf("Location y: [%p]\n", &y);
        printf("Location z: [%p]\n", &z);
    }
};

struct Derivate : public Base 
{
    uint32_t a;

    Derivate()
    {
        a = 234;
    }
    void printVars()
    {
        printf("Location x: [%p]\n", &x);
        printf("Location y: [%p]\n", &y);
        printf("Location z: [%p]\n", &z);
        printf("Location a: [%p]\n", &a);
    }
};

//======== Helper Functions =========================================

//======== Main Function ============================================
int main()
{
    printf("[+] Spawn base...\n");
    Base base;
    dump_instance("Instance of base", base);
    base.printVars();

    printf("\n");

    printf("[+] Spawn derivate...\n");
    Derivate derivate;
    dump_instance("Instance of derivate", derivate);
    derivate.printVars();

    return 0;
}

//======== Implementations ==========================================