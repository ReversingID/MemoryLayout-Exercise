/*
Virtual Table atau Virtual Method Table

Di dalam dunia OO (object-oriented), polimorfisme menyebabkan class
turunan dapat melakukan override terhadap perilaku fungsi-fungsi yang
diwariskan dari Base.

C++ menggunakan konsep virtual table untuk mengimplementasikan hal ini.

Apa yang terjadi di vtable jika sebuah class diturunkan dari beberapa class?

teruji di:
    - TDM GCC 5.1.0 dan MinGW GCC 7.3.0 (x64)

Compile:
    $ g++ multi-base.cpp -std=c++11 -o multi-base

Run:
    $ multi-base

Untuk mempermudah analisis, kita dapat memaksa compiler untuk mengeluarkan
representasi vtable dan struktur lainnya yang digunakan.
    (GCC)
    $ g++ -g -fdump-class-hierarchy -std=c++11 multi-base.cpp

    (MSVC)
    $ cl.exe /d1 reportAllClassLayout multi-base.cpp

*/
#include <iostream>
#include "../util.hpp"

/*
Amati alamat dari setiap komponen.
Questions:
    - Apakah terdapat dua atau lebih entry di vtable yang menunjuk alamat sama?
      Mengapa demikian?
    - Mengapa Derivate memiliki lebih dari 1 vtable?
    - Apa yang terjadi pada kedua vtable bila E() di-override pada Derivate.

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
    - Base1::~Base1()       (base object destructor)
    - Base1::~Base1()       (deleting destructor)
    - Base1::B()
    - Base1::C()
*/
class Base1 
{
public:
    int id1;
    Base1(int id) : id1(id)  { }
    virtual ~Base1()        { }

            void A()        { std::cout << "-  Base[" << id1 << "]::A" << std::endl; }
    virtual void B()        { std::cout << "-  Base[" << id1 << "]::B" << std::endl; }
    virtual void C()        { std::cout << "-  Base[" << id1 << "]::C" << std::endl; }
};

/*
Base2 sebagai salah satu kelas dasar.

Memory layout:
    - Base2::vtable         (pointer ke vtable Base)
    - Base2::id2

The vtable layout:
    - Base2::~Base1()       (base object destructor)
    - Base2::~Base1()       (deleting destructor)
    - Base2::D()
    - Base2::E()
*/
class Base2 
{
public:
    int id2;
    Base2(int id) : id2(id) { }
    virtual ~Base2()        { }

            void A()        { std::cout << "-  Base2::A" << std::endl; }
    virtual void D()        { std::cout << "-  Base2::D" << std::endl; }
    virtual void E()        { std::cout << "-  Base2::E" << std::endl; }
};

/*
Derivate diturunkan dari dua kelas sehingga memiliki 2 vtable.

Memory layout:
    - Derivate::vtable      (pointer ke vtable Derivate)
    - Base1::id1
    - Base2::vtable         (pointer ke vtable Base2)
    - Base2::id2

The vtable1 layout:
    - Derivate::~Derivate()     (base object destructor)
    - Derivate::~Derivate()     (deleting destructor)
    - Base1::B()
    - Derivate::C()
    - Derivate::D()

The vtable2 layout:
    - Base2::~Base2()     (base object destructor)
    - Base2::~Base2()     (deleting destructor)
    - Base2::D()
    - Base2::E()
*/
class Derivate final : public Base1, public Base2
{
public:
     Derivate(int id) : Base1(id), Base2(id) { }
    ~Derivate()       { }

    void C() override { std::cout << "-  Derivate[" << id1 << "]::C" << std::endl; }
    void D() override { std::cout << "-  Derivate[" << id2 << "]::D" << std::endl; }
};

//======== Helper Functions =========================================

//======== Main Function ============================================
int main()
{
    Base1 base1(1);
    Base2 base2(2);
    Derivate derivate(3);

    dump_instance("instance of base1", base1, 4);
    dump_instance("instance of base2", base2, 4);
    dump_instance("instance of Derivate", derivate, 5);

    // Dump vtable kedua dari derivate
    dump_vtable(*(reinterpret_cast<uintptr_t*>(&derivate) + 2), 4);

    return 0;
}