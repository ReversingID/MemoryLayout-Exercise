/*
    Instance Order (C++)
    Archive of Reversing.ID

Objective:
    Identifikasi urutan instansiasi objek dalam inheritance.

    Jika sebuah class diturunkan dari class lain, bagaimana ia dibangun?
    Bagaimana jika ia diturunkan dari lebih dari 1 class?

Compile:
    (GCC)  
    $ g++ instance-order2.cpp -std=c++11 -o instance-order2
    
    (LLVM/Clang) 
    $ clang++ instance-order2.cpp -o instance-order2

    (MSVC)
    $ cl instance-order2.cpp

Run:
    $ instance-order2
*/

#include "../util.hpp"

/*
    Amati urutan instansiasi objek.

Pertanyaan:
    - Apabila dalam suatu scope terdapat lebih dari suatu objek yang
      harus diinstansiasi, bagaimana urutan instansiasinya?

Kesimpulan:
    Ketika menginstansiasi sebuah class dengan dua atau lebih base, 
    maka class yang menjadi base (parent) akan diinstansiasi secara
    berurutan berdasarkan deklarasi.
*/

//======== Type Definitions =========================================

struct Base1
{
    Base1 () 
    {
        printf ("   Hello from Base1\n");
    }
    ~Base1 ()
    {
        printf ("   Bye from Base1\n");
    }
};

struct Base2
{
    Base2 ()
    {
        printf ("   Hello from Base2\n");
    }
    ~Base2 ()
    {
        printf ("   Bye from Base2\n");
    }
};

struct Derivate : public Base1, public Base2 
{
    Derivate ()
    {
        printf ("   Hello from Derivate\n");
    }
    ~Derivate ()
    {
        printf ("   Bye from Derivate\n");
    }
};

//======== Helper Functions =========================================

//======== Main Function ============================================

int main ()
{
    printf ("[+] Spawning Derivate...\n");
    Derivate derivate;

    return 0;
}

//======== Implementations ==========================================