/*
    Virtual Table (C++)
    Archive of Reversing.ID

Objective:
    Identifikasi letak vtable beserta isinya.

    Virtual Table disebut juga sebagai Virtual Method Table.

    Dalam Object Oriented Programming, setiap kelas yang diturunkan dari
    kelas lain akan mewarisi method-method yang terdefinisi di kelas induk.
    Kelas turunan dapat pula mengubah perilaku dari method yang diwarisi.
    Dikenal juga dengan sebutan override.
    
    C++ mengimplementasikan Virtual Table untuk mendukung overriding.

    Bagaimana representasi layout dari vtable di memory?

teruji di:
    - TDM GCC 5.1.0 dan MinGW GCC 7.3.0 (x64)
    - LLVM/Clang 12.0

Compile:
    (GCC)
    $ g++ layout.cpp -std=c++11 -o layout

    (LLVM/Clang)
    $ clang++ layout.cpp -o layout

    (MSVC)
    $ cl layout.cpp

Run:
    $ layout

Dump vtable:
    Dump representasi vtable dan struktur lain untuk keperluan analisis.

    (GCC)
    $ g++ -g -fdump-class-hierarchy -std=c++11 layout.cpp

    (LLVM/Clang)
    $ clang++ -fdump-record-layouts layout.cpp

    (MSVC)
    $ cl.exe /d1 reportAllClassLayout layout.cpp
*/

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
    - ClassA::~ClassA ()
    - ClassA::B ()
*/
class ClassA 
{
    int id;
public:
    ClassA (int id) : id(id) { }
    virtual ~ClassA ()       { }

    void A ()                { printf ("-  ClassA[%d]::A\n", id); }
    virtual void B ()        { printf ("-  ClassA[%d]::B\n", id); }
};

/*
Memory layout:
    - ClassB::vtable        (pointer ke vtable ClassB)
    - ClassB::id

The vtable layout:
    - ClassB::A ()
    - ClassB::B ()
*/
class ClassB
{
    int id;
public:
    ClassB (int id) : id(id) { }
    ~ClassB ()               { }

    virtual void A ()        { printf ("-  ClassB[%d]::A\n", id); } 
    virtual void B ()        { printf ("-  ClassB[%d]::B\n", id); }
};

//======== Helper Functions =========================================

//======== Main Function ============================================
int main ()
{
    ClassA InstanceA (1);
    ClassB InstanceB (2);

    dump_instance ("instance of ClassA", InstanceA, true);
    dump_instance ("instance of ClassB", InstanceB, true);

    return 0;
}