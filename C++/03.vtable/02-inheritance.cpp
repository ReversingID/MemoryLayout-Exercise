/*
Virtual Table atau Virtual Method Table

Di dalam konsep OO (object-oriented), setiap kelas yang diturunkan dari
kelas lain akan mewarisi method-method yang terdefinisi di kelas induk.
Kelas turunan dapat pula mengubah perilaku dari method yang diwarisi, 
atau dikenal juga dengan sebutan override.

C++ menggunakan konsep virtual table untuk mengimplementasikan hal ini.

Bagaimana representasi layout dari vtable di memory ketika inheritance terjadi?

teruji di:
    - TDM GCC 5.1.0 dan MinGW GCC 7.3.0 (x64)

Compile:
    $ g++ inheritance.cpp -std=c++11 -o inheritance

Run:
    $ inheritance

Untuk mempermudah analisis, kita dapat memaksa compiler untuk mengeluarkan
representasi vtable dan struktur lainnya yang digunakan.
    (GCC)
    $ g++ -g -fdump-class-hierarchy -std=c++11 inheritance.cpp

    (MSVC)
    $ cl.exe /d1 reportAllClassLayout inheritance.cpp

*/
#include <iostream>
#include "../util.hpp"

/*
Amati alamat dari setiap komponen.
Pertanyaan:
    - Apakah terdapat dua atau lebih entry di vtable yang menunjuk alamat sama?
      Mengapa demikian?
    - Bagaimana jika ClassA::A() tidak didefinisikan sebagai virtual?
    - Bandingkan antara hasil yang diberikan oleh GCC dan MSVC. 
      Apakah terdapat perbedaan struktur?
    - Mengapa C memiliki vtable meskipun tidak mendeklarasikan fungsi virtual?
    - Mengapa D memiliki vtable meskipun tidak mendeklarasikan fungsi virtual?

Kesimpulan:
    Ketika sebuah class diturunkan dari class lain, ia akan mewarisi vtable tersebut.

*/

//======== Type Definitions =========================================
/*
Memory layout:
    - ClassA::vtable        (pointer ke vtable ClassA)
    - ClassA::id

The vtable layout:
    - ClassA::~ClassA()     (base object destructor)
    - ClassA::~ClassA()     (deleting destructor)
    - ClassA::A()
*/
class ClassA 
{
protected:
    int id;
public:
    ClassA(int id) : id(id) { }
    virtual ~ClassA()       { }

    virtual void A()        { std::cout << "-  ClassA[" << id << "]::A" << std::endl; }
};


/*
Memory layout:
    - ClassB::vtable        (pointer ke vtable ClassB)
    - ClassB::id

The vtable layout:
    - ClassB::B()
*/
class ClassB
{
protected:
    int id;
public:
     ClassB(int id) : id(id) { }
    ~ClassB()                { }

    virtual void B()        { std::cout << "-  ClassB[" << id << "]::B" << std::endl; }
};


/*
Memory layout:
    - ClassC::vtable        (pointer ke vtable ClassC)
    - ClassA::id

The vtable layout:
    - ClassC::~ClassC()     (base object destructor)
    - ClassC::~ClassC()     (deleting destructor)
    - ClassC::A()
*/
class ClassC : public ClassA
{
public:
     ClassC(int id) : ClassA(id) { }
    ~ClassC()                    { }
};

/*
Memory layout:
    - ClassD::vtable        (pointer ke vtable ClassD)
    - ClassA::id
    - ClassB::id

The vtable layout:
    - ClassD::~ClassD()     (base object destructor)
    - ClassD::~ClassD()     (deleting destructor)
    - ClassA::A()
*/
class ClassD : public ClassC
{
public:
     ClassD(int id) : ClassC(id) { }
    ~ClassD()       { }
};

//======== Helper Functions =========================================

//======== Main Function ============================================
int main()
{
    ClassA InstanceA(1);
    ClassB InstanceB(2);
    ClassC InstanceC(3);
    ClassD InstanceD(4);

    // Menyebutkan banyaknya fungsi secara manual
    dump_instance("instance of ClassA", InstanceA, 4);
    printf("-------------------------\n\n"); 
    dump_instance("instance of ClassB", InstanceB, 4);
    printf("-------------------------\n\n");
    dump_instance("instance of ClassC", InstanceC, 4);
    printf("-------------------------\n\n");
    dump_instance("instance of ClassD", InstanceD, 4);
    printf("-------------------------\n\n");

    InstanceC.A();
    InstanceD.A();

    return 0;
}