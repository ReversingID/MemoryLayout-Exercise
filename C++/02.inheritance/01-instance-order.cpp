/*
Identifikasi tata letak memori (memory-layout) sebuah objek.
Jika sebuah class diturunkan dari class lain, bagaimana ia dibangun?

Compile:
    (GCC)  
    $ g++ instance-order.cpp -std=c++11 -o instance-order
    
    (LLVM) 
    $ clang++ instance-order.cpp -o instance-order

    (MSVC)
    $ cl instance-order.cpp

Run:
    $ instance-order
*/
#include "../util.hpp"

/*
Amati urutan instansiasi objek.
Pertanyaan:
    - Apabila dalam suatu scope terdapat lebih dari suatu objek yang
      harus diinstansiasi, bagaimana urutan instansiasinya?
    - Apabila suatu class memiliki beberapa class lain sebagai anggota,
      bagaimana urutan instansiasinya?

Kesimpulan:
    - Ketika objek diinstansiasi, constructor akan dipanggil secara 
      berurutan dari parent ke child.
    - Ketika objek dihancurkan, destructor akan dipanggil dari 
      child ke parent.
*/

//======== Type Definitions =========================================
struct Base
{
    Base() 
    {
        printf("Hello from Base\n");
    }
    ~Base()
    {
        printf("Bye from Base\n");
    }
};

struct Derivate : public Base 
{
    Derivate()
    {
        printf("Hello from Derivate\n");
    }
    ~Derivate()
    {
        printf("Bye from Derivate\n");
    }
};

struct DerivateMore : public Derivate
{
    DerivateMore()
    {
        printf("Hello from DerivateMore\n");
    }
    ~DerivateMore()
    {
        printf("Bye from DerivateMore\n");
    }
};

//======== Helper Functions =========================================

//======== Main Function ============================================
int main()
{
    // Spawn Base di dalam scope
    {
        printf("[+] Spawning Base...\n");
        Base base;
    }

    printf("\n");

    // Spawn Derivate di dalam scope
    {
        printf("[+] Spawning Derivate...\n");
        Derivate derivate;
    }
    
    printf("\n");

    // Spawn DerivateMore di dalam scope
    {
        printf("[+] Spawning DerivateMore...\n");
        DerivateMore derivate_more;
    }

    return 0;
}

//======== Implementations ==========================================