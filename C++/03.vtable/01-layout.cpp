/*
Virtual Table atau Virtual Method Table

Di dalam konsep OO (object-oriented), setiap kelas yang diturunkan dari
kelas lain akan mewarisi method-method yang terdefinisi di kelas induk.
Kelas turunan dapat pula mengubah perilaku dari method yang diwarisi, 
atau dikenal juga dengan sebutan override.

C++ menggunakan konsep virtual table untuk mengimplementasikan hal ini.

Bagaimana representasi layout dari vtable di memory?

teruji di:
    - TDM GCC 5.1.0 dan MinGW GCC 7.3.0 (x64)

Compile:
    $ g++ layout.cpp -std=c++11 -o layout

Run:
    $ layout

Untuk mempermudah analisis, kita dapat memaksa compiler untuk mengeluarkan
representasi vtable dan struktur lainnya yang digunakan.
    (GCC)
    $ g++ -g -fdump-class-hierarchy -std=c++11 layout.cpp

    (MSVC)
    $ cl.exe /d1 reportAllClassLayout layout.cpp

*/
#include <iostream>
#include "../util.hpp"

/*
Amati alamat dari setiap komponen.
Pertanyaan:
    - Apakah dua class menunjuk alamat vtable yang sama?
    - Bandingkan layout vtable dari ClassA dan ClassB, apa perbedaannya?
    - Mengapa tidak semua fungsi ada di vtable?
    - Apakah terdapat dua atau lebih entry di vtable yang menunjuk alamat sama?
      Mengapa demikian?

Kesimpulan:
    Urutan entry vtable serupa dengan deklarasi virtual function di source code.
*/

//======== Type Definitions =========================================
/*
Memory layout:
    - ClassA::vtable        (pointer ke vtable ClassA)
    - ClassA::id

The vtable layout:
    - ClassA::~ClassA()     (base object destructor)
    - ClassA::~ClassA()     (deleting destructor)
    - ClassA::B()
*/
class ClassA 
{
    int id;
public:
    ClassA(int id) : id(id) { }
    virtual ~ClassA()       { }

    void A()                { std::cout << "-  ClassA[" << id << "]::A" << std::endl; }
    virtual void B()        { std::cout << "-  ClassA[" << id << "]::B" << std::endl; }
};

/*
Memory layout:
    - ClassB::vtable        (pointer ke vtable ClassB)
    - ClassB::id

The vtable layout:
    - ClassB::A()
    - ClassB::B()
*/
class ClassB
{
    int id;
public:
     ClassB(int id) : id(id) { }
    ~ClassB()       { }

    virtual void A()        { std::cout << "-  ClassB[" << id << "]::A" << std::endl; } 
    virtual void B()        { std::cout << "-  ClassB[" << id << "]::B" << std::endl; }
};

//======== Helper Functions =========================================

//======== Main Function ============================================
int main()
{
    ClassA InstanceA(1);
    ClassB InstanceB(2);

    dump_instance("instance of ClassA", InstanceA, 3);    
    dump_instance("instance of ClassB", InstanceB, 2);

    return 0;
}