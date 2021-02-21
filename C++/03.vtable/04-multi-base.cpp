/*
    Multiple Base Class (C++)
    Archive of Reversing.ID

Objective:
    Identifikasi letak vtable beserta isinya.

    Virtual Table disebut juga sebagai Virtual Method Table.

    Dalam Object Oriented Programming, setiap kelas yang diturunkan dari
    kelas lain akan mewarisi method-method yang terdefinisi di kelas induk.
    Kelas turunan dapat pula mengubah perilaku dari method yang diwarisi.
    Dikenal juga dengan sebutan override.
    
    C++ mengimplementasikan Virtual Table untuk mendukung overriding.

    Apa yang terjadi di vtable jika sebuah class diturunkan dari beberapa class?

teruji di:
    - TDM GCC 5.1.0 dan MinGW GCC 7.3.0 (x64)
    - LLVM/Clang 12.0

Compile:
    (GCC)
    $ g++ multi-base -std=c++11 -o multi-base

    (LLVM/Clang)
    $ clang++ multi-base -o multi-base

    (MSVC)
    $ cl multi-base

Run:
    $ multi-base

Dump vtable:
    Dump representasi vtable dan struktur lain untuk keperluan analisis.

    (GCC)
    $ g++ -g -fdump-class-hierarchy -std=c++11 multi-base

    (LLVM/Clang)
    $ clang++ -fdump-record-layouts multi-base

    (MSVC)
    $ cl.exe /d1 reportAllClassLayout multi-base
*/

#include "../util.hpp"

/*
    Amati alamat dari setiap komponen.

Pertanyaan:
    - Apakah terdapat dua atau lebih entry di vtable yang menunjuk alamat sama?
      Mengapa demikian?
    - Mengapa Derivate memiliki lebih dari 1 vtable?
    - Apa yang terjadi pada kedua vtable bila E () di-override pada Derivate.

Kesimpulan:
    Entry di vtable akan serupa di class turunan selama override tidak terjadi.
*/

//======== Type Definitions =========================================

/*
Base1 sebagai salah satu kelas dasar.

Memory layout:
    - Base1::vtable         (pointer ke vtable Base)
    - Base1::id1

The vtable layout:
    - Base1::~Base1 ()       (base object destructor)
    - Base1::~Base1 ()       (deleting destructor)
    - Base1::B ()
    - Base1::C ()
*/
class Base1 
{
public:
    int id1;
    Base1 (int id) : id1 (id)  { }
    virtual ~Base1 ()        { }

            void A ()        { printf ("-  Base1[%d]::A", id1); }
    virtual void B ()        { printf ("-  Base1[%d]::B", id1); }
    virtual void C ()        { printf ("-  Base1[%d]::C", id1); }
};

/*
Base2 sebagai salah satu kelas dasar.

Memory layout:
    - Base2::vtable         (pointer ke vtable Base)
    - Base2::id2

The vtable layout:
    - Base2::~Base1 ()       (base object destructor)
    - Base2::~Base1 ()       (deleting destructor)
    - Base2::D ()
    - Base2::E ()
*/
class Base2 
{
public:
    int id2;
    Base2 (int id) : id2 (id) { }
    virtual ~Base2 ()        { }

            void A ()        { printf ("-  Base2[%d]::A", id2); }
    virtual void D ()        { printf ("-  Base2[%d]::D", id2); }
    virtual void E ()        { printf ("-  Base2[%d]::E", id2); }
};

/*
Derivate diturunkan dari dua kelas sehingga memiliki 2 vtable.

Memory layout:
    - Derivate::vtable      (pointer ke vtable Derivate)
    - Base1::id1
    - Base2::vtable         (pointer ke vtable Base2)
    - Base2::id2

The vtable1 layout:
    - Derivate::~Derivate ()     (base object destructor)
    - Derivate::~Derivate ()     (deleting destructor)
    - Base1::B ()
    - Derivate::C ()
    - Derivate::D ()

The vtable2 layout:
    - Base2::~Base2 ()     (base object destructor)
    - Base2::~Base2 ()     (deleting destructor)
    - Base2::D ()
    - Base2::E ()
*/
class Derivate final : public Base1, public Base2
{
public:
     Derivate (int id) : Base1 (id), Base2 (id) { }
    ~Derivate ()       { }

    void C () override { printf ("-  Derivate[%d]::C", id1 ); }
    void D () override { printf ("-  Derivate[%d]::D", id2 ); }
};

//======== Helper Functions =========================================

//======== Main Function ============================================

int main ()
{
    Base1 base1 (1);
    Base2 base2 (2);
    Derivate derivate (3);

    dump_instance ("instance of base1", base1, 4);
    dump_instance ("instance of base2", base2, 4);
    dump_instance ("instance of Derivate", derivate, 5);

    // Dump vtable kedua dari derivate
    dump_vtable (* (reinterpret_cast<uintptr_t*> (&derivate) + 2));

    return 0;
}