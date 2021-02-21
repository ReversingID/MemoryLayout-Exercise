/*
    Type Cast (C++)
    Archive of Reversing.ID

Objective:
    Identifikasi tata letak memori (memory-layout) sebuah objek.

    Dalam dunia Object Oriented, sebuah class dapat memiliki hubungan 
    parent-child dengan class lain. Sebuah class dapat memiliki lebih
    dari satu parent dan diturunkan ke lebih dari satu child.
    Hubungan antar class ini dapat diperlihatkan sebagai hirarki.

    Upcasting adalah mengubah reference atau pointer bertipe child/derived
    sehingga dianggap bertipe parent/base.
    
    Downcasting adalah kebalikannya, mengubah reference atau pointer bertipe
    parent/base sehingga dianggap bertipe derived/child.

Compile:
    (GCC)  
    $ g++ cast.cpp -std=c++11 -o cast
    
    (LLVM/Clang) 
    $ clang++ cast.cpp -o cast

    (MSVC)
    $ cl cast.cpp

Run:
    $ cast
*/

#include "../util.hpp"

/*
    Amati alamat dari masing-masing elemen berikut.

Pertanyaan:
    Objek
    - Ketika upcast derivate ke base1 atau base2, alamat mana yang ditunjuk?
    - Kenapa alamat Derivate sama dengan ketika Derivate upcast ke Base1?
    - Apa yang terjadi ketika pointer base menunjuk ke objek base namun 
      mengalami downcast sehingga menunjuk tipe derivate?
    - Saat Base1 downcast ke Derivate, variabel-variabel menunjuk kemana?
    - Saat Base2 downcast ke Derivate, objek menunjuk kemana?
    - ganti C-style cast dengan dynamic_cast<> saat downcast, 
      apa yang terjadi?
    
    Functions
    - Untuk setiap casting yang terjadi, function() manakah yang dipanggil?


dynamic_cast<>
    digunakan untuk upcast maupun downcast.
    tujuan utama penggunaannya adalah untuk menjamin hasil konversi
    merupakan objek utuhdan valid dengan tipe yang ditargetkan.
*/

//======== Type Definitions =========================================

struct Base1
{
    uint32_t x, y;

    Base1 () 
    {
        x = 0x87;
        y = 0xB6;
    }

    void function ()
    {
        printf ("[%p] Hello Base1! x:%x y:%x\n", &Base1::function, x, y);
    }
};

struct Base2
{
    uint32_t z;

    Base2 ()
    {
        z = 0xEA;
    }
    
    void function ()
    {
        printf ("[%p] Hello Base2! z:%x\n", &Base2::function, z);
    }
};

// class Derivate diturunkan dari Base1 dan Base2 sehingga
// dapat dilakukan upcast ke keduanya.
struct Derivate : public Base1, public Base2 
{
    uint32_t w;

    Derivate ()
    {
        w = 0;
    }

    void function ()
    {
        printf ("[%p] Hello Derivate! x:%x y:%x z:%x w:%x\n", 
            &Derivate::function, x, y, z, w);
    }
};

//======== Helper Functions =========================================

//======== Main Function ============================================

int main ()
{
    Base1    base1;
    Base2    base2;
    Derivate derivate;

    Base1* pbase1;
    Base2* pbase2;
    Derivate* pderivate;

    printf ("[+] base1 is at    [%p] (size %zu)\n", &base1, sizeof (base1));
    printf ("[+] base2 is at    [%p] (size %zu)\n", &base2, sizeof(base2));
    printf ("[+] derivate is at [%p] (size %zu)\n", &derivate, sizeof (derivate));
    derivate.function ();
    base1.function ();
    base2.function ();

    printf ("\n============================\n\n");

    printf ("[+] Upcast derivate to parent\n");
    printf ("   [-] to Base1...\n");
    pbase1 = dynamic_cast<Base1*> (&derivate);
    printf ("   [-] I'm located at: [%p]\n", pbase1);
    pbase1->function ();
    printf ("\n");
    printf ("   [-] to Base2...\n");
    pbase2 = dynamic_cast<Base2*> (&derivate);
    printf ("   [-] I'm located at: [%p]\n", pbase2);
    pbase2->function ();

    printf ("\n============================\n\n");
    
    printf ("[+] Downcast base to child\n");
    printf ("   [-] from Base1...\n");
    pderivate = (Derivate*)&base1;
    printf ("   [-] I'm located at: [%p]\n", pderivate);
    pderivate->function ();
    printf ("\n");
    printf ("   [-] from Base2...\n");
    pderivate = (Derivate*)&base2;
    printf ("   [-] I'm located at: [%p]\n", pderivate);
    pderivate->function ();

    return 0;
}

//======== Implementations ==========================================