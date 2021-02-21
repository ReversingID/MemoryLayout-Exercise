/*
    Inheritance Layout (C++)
    Archive of Reversing.ID

Objective:
    Identifikasi tata letak memori (memory-layout) sebuah objek.

    Jika sebuah class diturunkan dari class lain, bagaimana ia 
    direpresentasikan?

Compile:
    (GCC)  
    $ g++ layout.cpp -std=c++11 -o layout
    
    (LLVM/Clang) 
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
    Objek:
    - Berapa ukuran setiap objek?

    Variables
    Identifikasi variabel dan dapatkan alamatnya.
    - Apabila suatu class diturunkan dari class lain, bagaimana urutan 
      variabel di memory?

Kesimpulan: 
    Sebuah class diturunkan dari class lain akan mewarisi data yang 
    diletakkan berdampingan dengan data yang ia miliki.
*/

//======== Type Definitions =========================================

struct Base
{
    uint32_t x, y, z;

    Base () 
    {
        x = 135;
        y = 182;
    }
    void printVars ()
    {
        printf ("Location x: [%p]\n", &x);
        printf ("Location y: [%p]\n", &y);
        printf ("Location z: [%p]\n", &z);
    }
    void printFuncs ()
    {
        printf ("Location of printVars   : [%p]\n", &Base::printVars);
        printf ("Location of printFuncs  : [%p]\n", &Base::printFuncs);
    }
};

struct Derivate : public Base 
{
    uint32_t a;

    Derivate ()
    {
        a = 234;
    }
    void printVars ()
    {
        printf ("Location x: [%p]\n", &x);
        printf ("Location y: [%p]\n", &y);
        printf ("Location z: [%p]\n", &z);
        printf ("Location a: [%p]\n", &a);
    }
    void printFuncs ()
    {
        printf ("Location of printVars   : [%p]\n", &Derivate::printVars);
        printf ("Location of printFuncs  : [%p]\n", &Derivate::printFuncs);
    }
};

//======== Helper Functions =========================================

//======== Main Function ============================================

int main ()
{
    printf ("[+] Spawn base...\n");
    Base base;
    dump_instance ("Instance of base", base);
    base.printVars ();
    base.printFuncs ();

    printf ("\n");

    printf ("[+] Spawn derivate...\n");
    Derivate derivate;
    dump_instance ("Instance of derivate", derivate);
    derivate.printVars ();
    derivate.printFuncs ();

    return 0;
}

//======== Implementations ==========================================