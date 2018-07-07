/*
Virtual Table atau Virtual Method Table

Di dalam dunia OO (object-oriented), polimorfisme menyebabkan class
turunan dapat melakukan override terhadap perilaku fungsi-fungsi yang
diwariskan dari Base.

C++ menggunakan konsep virtual table untuk mengimplementasikan hal ini.

Apa yang terjadi di vtable jika sebuah method di-override?

teruji di:
    - TDM GCC 5.1.0 dan MinGW GCC 7.3.0 (x64)

Compile:
    $ g++ override.cpp -std=c++11 -o override

Run:
    $ override

Untuk mempermudah analisis, kita dapat memaksa compiler untuk mengeluarkan
representasi vtable dan struktur lainnya yang digunakan.
    (GCC)
    $ g++ -g -fdump-class-hierarchy -std=c++11 override.cpp

    (MSVC)
    $ cl.exe /d1 reportAllClassLayout override.cpp

*/
#include <iostream>
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

    void A()                { std::cout << "-  Base[" << id << "]::A" << std::endl; }
    virtual void B()        { std::cout << "-  Base[" << id << "]::B" << std::endl; }
    virtual void C()        { std::cout << "-  Base[" << id << "]::C" << std::endl; }
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

    // void B() override           { std::cout << "-  Derivate[" << id << "]::B" << std::endl; } 
    void C() override           { std::cout << "-  Derivate[" << id << "]::C" << std::endl; }
};

//======== Helper Functions =========================================

//======== Main Function ============================================
int main()
{
    Base base(1);
    Derivate derivate(2);
    Base *pbase = new Derivate(3);

    dump_instance("instance of base", base, 4);    
    dump_instance("instance of Derivate", derivate, 4);    
    dump_instance("instance of pointer to Derivate", *pbase, 4);

    // Cobalah untuk memanggil B() dari setiap instance!

    return 0;
}