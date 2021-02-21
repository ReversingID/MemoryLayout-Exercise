/*
    VTable Inheritance (C++)
    Archive of Reversing.ID

Objective:
    Identifikasi letak vtable beserta isinya.

    Virtual Table disebut juga sebagai Virtual Method Table.

    Dalam Object Oriented Programming, setiap kelas yang diturunkan dari
    kelas lain akan mewarisi method-method yang terdefinisi di kelas induk.
    Kelas turunan dapat pula mengubah perilaku dari method yang diwarisi.
    Dikenal juga dengan sebutan override.
    
    C++ mengimplementasikan Virtual Table untuk mendukung overriding.

    Bagaimana representasi layout dari vtable di memory dalam inheritance?

teruji di:
    - TDM GCC 5.1.0 dan MinGW GCC 7.3.0 (x64)
    - LLVM/Clang 12.0

Compile:
    (GCC)
    $ g++ inheritance.cpp -std=c++11 -o inheritance

    (LLVM/Clang)
    $ clang++ inheritance.cpp -o inheritance

    (MSVC)
    $ cl inheritance.cpp

Run:
    $ inheritance

Dump vtable:
    Dump representasi vtable dan struktur lain untuk keperluan analisis.

    (GCC)
    $ g++ -g -fdump-class-hierarchy -std=c++11 inheritance.cpp

    (LLVM/Clang)
    $ clang++ -fdump-record-layouts inheritance.cpp

    (MSVC)
    $ cl.exe /d1 reportAllClassLayout inheritance.cpp
*/

#include "../util.hpp"

/*
    Amati alamat dari setiap komponen.

Pertanyaan:
    - Apakah terdapat dua atau lebih entry di vtable yang menunjuk alamat sama?
      Mengapa demikian?
    - Bagaimana jika ClassA::A () tidak didefinisikan sebagai virtual?
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
    - ClassA::~ClassA ()     (base object destructor)
    - ClassA::~ClassA ()     (deleting destructor)
    - ClassA::A ()
*/
class ClassA 
{
protected:
    int id;
public:
    ClassA (int id) : id (id) { }
    virtual ~ClassA ()       { }

    virtual void A ()        { printf ("-  ClassA[%d]::A\n", id); }
};


/*
Memory layout:
    - ClassB::vtable        (pointer ke vtable ClassB)
    - ClassB::id

The vtable layout:
    - ClassB::B ()
*/
class ClassB
{
protected:
    int id;
public:
     ClassB (int id) : id (id) { }
    ~ClassB ()                { }

    virtual void B ()        { printf ("-  ClassB[%d]::B\n", id); }
};


/*
Memory layout:
    - ClassC::vtable        (pointer ke vtable ClassC)
    - ClassA::id

The vtable layout:
    - ClassC::~ClassC ()     (base object destructor)
    - ClassC::~ClassC ()     (deleting destructor)
    - ClassC::A ()
*/
class ClassC : public ClassA
{
public:
     ClassC (int id) : ClassA (id) { }
    ~ClassC () { }
};

/*
Memory layout:
    - ClassD::vtable        (pointer ke vtable ClassD)
    - ClassA::id
    - ClassB::id

The vtable layout:
    - ClassD::~ClassD ()     (base object destructor)
    - ClassD::~ClassD ()     (deleting destructor)
    - ClassA::A ()
*/
class ClassD : public ClassC
{
public:
     ClassD (int id) : ClassC (id) { }
    ~ClassD () { }
};

//======== Helper Functions =========================================

//======== Main Function ============================================
int main ()
{
    ClassA InstanceA (1);
    ClassB InstanceB (2);
    ClassC InstanceC (3);
    ClassD InstanceD (4);

    // Menyebutkan banyaknya fungsi secara manual
    dump_instance ("instance of ClassA", InstanceA, true);
    printf ("-------------------------\n\n"); 
    dump_instance ("instance of ClassB", InstanceB, true);
    printf ("-------------------------\n\n");
    dump_instance ("instance of ClassC", InstanceC, true);
    printf ("-------------------------\n\n");
    dump_instance ("instance of ClassD", InstanceD, true);
    printf ("-------------------------\n\n");

    InstanceC.A ();
    InstanceD.A ();

    return 0;
}