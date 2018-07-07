/*
Identifikasi tata letak memori (memory-layout) sebuah objek.

Di dalam dunia OO (object-oriented), sebuah class dapat memiliki hubungan parent-child
dengan class lain. Sebuah class dapat memiliki lebih dari satu base dan dapat pula
memiliki lebih dari satu turunan. Hubungan antar class ini dapat diperlihatkan
sebagai hirarki.

Upcasting adalah mengubah reference atau pointer bertipe derived sehingga dianggap
bertipe base.

Downcasting adalah kebalikannya, mengubah reference atau pointer bertipe base 
sehingga dianggap bertipe derived.

Compile:
    (GCC)  
    $ g++ cast.cpp -std=c++11 -o cast
    
    (LLVM) 
    $ clang++ cast.cpp -o cast

    (MSVC)
    $ cl cast.cpp

Run:
    $ cast
*/
#include "../util.hpp"

/*
dynamic_cast<>
    digunakan untuk upcast maupun downcast.
    tujuan utama penggunaannya adalah untuk menjamin hasil konversi
    merupakan objek utuhdan valid dengan tipe yang ditargetkan.

Amati alamat dari masing-masing elemen berikut.
Pertanyaan:
    - Apa yang terjadi jika Sebuah pointer base menunjuk ke objek base, 
      namun mengalami downcast sehingga menunjuk tipe turunan?
    - ganti C-style cast dengan dynamic_cast<> pada saat downcast, apa 
      yang terjadi?
*/

//======== Type Definitions =========================================
struct Base1
{
    uint32_t x, y;

    Base1() 
    {
        x = 0x87;
        y = 0xB6;
    }

    void function(uint32_t a)
    {
        x = a;
        y = a + 45;
        printf("[%p] Hello Base1! %x %x\n", &Base1::function, x, y);
    }
};

struct Base2
{
    uint32_t z;

    Base2()
    {
        z = 0xEA;
    }
    
    void function(uint32_t a)
    {
        z = a;
        printf("[%p] Hello Base2! %x\n", &Base2::function, z);
    }
};

// class Derivate diturunkan dari Base1 dan Base2 sehingga
// dapat dilakukan upcast ke keduanya.
struct Derivate : public Base1, public Base2 
{
    uint32_t w;

    Derivate()
    {
        w = 0;
    }

    void function(uint32_t a)
    {
        w = a;
        printf("[%p] Hello Derivate! %x %x %x %x\n", &Derivate::function, x, y, z, w);
    }
};

//======== Helper Functions =========================================

//======== Main Function ============================================
int main()
{
    Base1    base1;
    Base2    base2;
    Derivate derivate;

    Base1* pbase1;
    Base2* pbase2;
    Derivate* pderivate;

    printf("[-] base1 is at    %p (size %d)\n", &base1, sizeof(base1));
    printf("[-] derivate is at %p (size %d)\n", &derivate, sizeof(derivate));
    derivate.function(0xFF);
    base1.function(0x87);

    printf("\n============================\n\n");

    printf("[+] Upcast derivate to parent\n");
    printf("[-] to Base1...\n");
    pbase1 = dynamic_cast<Base1*>(&derivate);
    printf("[-] I'm located at: %p\n", pbase1);
    pbase1->function(1);
    printf("\n");
    printf("[-] to Base2...\n");
    pbase2 = dynamic_cast<Base2*>(&derivate);
    printf("[-] I'm located at: %p\n", pbase2);
    pbase2->function(2);

    printf("\n============================\n\n");
    
    printf("[+] Downcast base to child\n");
    printf("[-] from Base1...\n");
    pderivate = (Derivate*)&base1;
    printf("[-] I'm located at: %p\n", pderivate);
    pderivate->function(3);
    printf("\n");
    printf("[-] from Base2...\n");
    pderivate = (Derivate*)&base2;
    printf("[-] I'm located at: %p\n", pderivate);
    pderivate->function(3);

    return 0;
}

//======== Implementations ==========================================