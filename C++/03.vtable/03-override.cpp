/*
    Override Function (C++)
    Archive of Reversing.ID

Objective:
    Identifikasi letak vtable beserta isinya.

    Virtual Table disebut juga sebagai Virtual Method Table.

    Dalam Object Oriented Programming, setiap kelas yang diturunkan dari
    kelas lain akan mewarisi method-method yang terdefinisi di kelas induk.
    Kelas turunan dapat pula mengubah perilaku dari method yang diwarisi.
    Dikenal juga dengan sebutan override.
    
    C++ mengimplementasikan Virtual Table untuk mendukung overriding.

    Apa yang terjadi di vtable jika sebuah method di-override?

teruji di:
    - TDM GCC 5.1.0 dan MinGW GCC 7.3.0 (x64)
    - LLVM/Clang 12.0

Compile:
    (GCC)
    $ g++ override.cpp -std=c++11 -o override

    (LLVM/Clang)
    $ clang++ override.cpp -o override

    (MSVC)
    $ cl override.cpp

Run:
    $ override

Dump vtable:
    Dump representasi vtable dan struktur lain untuk keperluan analisis.

    (GCC)
    $ g++ -g -fdump-class-hierarchy -std=c++11 override.cpp

    (LLVM/Clang)
    $ clang++ -fdump-record-layouts override.cpp

    (MSVC)
    $ cl.exe /d1 reportAllClassLayout override.cpp

*/

#include "../util.hpp"

/*
    Amati alamat dari setiap komponen.

Pertanyaan:
    - Apakah terdapat dua atau lebih entry di vtable yang menunjuk alamat sama?
      Mengapa demikian?
    - Apa yang terjadi jika Derivate::B() didefinisikan?

Kesimpulan:
    Entry di vtable akan serupa di class turunan selama override tidak terjadi.
*/

//======== Type Definitions =========================================

/*
Memory layout:
    - Base::vtable      (pointer ke vtable Base)
    - Base::id

The vtable layout:
    - Base::~Base()     (base object destructor)
    - Base::~Base()     (deleting destructor)
    - Base::B()
    - Base::C()
*/
class Base 
{
public:
    int id;

    Base(int id) : id(id)   { }
    virtual ~Base()         { }

    void A()                { printf ("-  Base[%d]::A\n", id); }
    virtual void B()        { printf ("-  Base[%d]::B\n", id); }
    virtual void C()        { printf ("-  Base[%d]::C\n", id); }
};


/*
Memory layout:
    - Derivate::vtable          (pointer ke vtable Derivate)
    - Base::id

The vtable layout:
    - Derivate::~Derivate()     (base object destructor)
    - Derivate::~Derivate()     (deleting destructor)
    - Base::B()
    - Derivate::C()
*/
class Derivate final : public Base 
{
public:
    Derivate(int id) : Base(id)  { }
    ~Derivate()                  { }

    // void B() override           { printf ("-  Derivate[%d]::B\n", id); } 
    void C() override           { printf ("-  Derivate[%d]::C\n", id); }
};

//======== Helper Functions =========================================

//======== Main Function ============================================

int main()
{
    Base base(1);
    Derivate derivate(2);
    Base *pbase = new Derivate(3);

    dump_instance("instance of base", base, true);    
    dump_instance("instance of Derivate", derivate, true);    
    dump_instance("instance of pointer to Derivate", *pbase, true);

    // Cobalah untuk memanggil B() dari setiap instance!

    return 0;
}