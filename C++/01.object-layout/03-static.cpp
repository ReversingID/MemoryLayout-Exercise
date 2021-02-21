/*
    Static Field (C++)
    Archive of Reversing.ID

Objective:
    Identifikasi tata letak memori (memory-layout) sebuah objek.

    Jika sebuah class memiliki satu atau lebih variabel static, dimana 
    ia berada?

Compile:
    (GCC)  
    $ g++ static.cpp -std=c++11 -o static
    
    (LLVM/Clang) 
    $ clang++ static.cpp -o static

    (MSVC)
    $ cl static.cpp

Run:
    $ static
*/

#include "../util.hpp"

/*
    Amati alamat setiap variabel dan fungsi.

Pertanyaan:
    Object
    - Berapa ukuran instance objek?

    Variables
    - Apakah terdapat anomali dari alamat variabel?
    - Di section apa setiap variabel berada?
    
Kesimpulan:
    Sebuah object dapat memiliki data yang static.
    Semua instance object akan merujuk ke variabel yang sama, lokasi 
    yang sama, dan berlaku selayaknya sebagai data global.
*/

//======== Type Definitions =========================================

class Example
{
    static int x;
    int y;
    int z;
public:
    Example () 
    {
        x = 135;
        y = 182;
        z = 15;
    }
    void printVars ()
    {
        printf ("Location x: [%p] | Value: %d\n", &x, x);
        printf ("Location y: [%p] | Value: %d\n", &y, y);
        printf ("Location z: [%p] | Value: %d\n", &z, z);
    }
    void printFuncs ()
    {
        printf ("Location of printVars   : [%p]\n", &Example::printVars);
        printf ("Location of printFuncs  : [%p]\n", &Example::printFuncs);
    }
};

// instance dari static field
int Example::x;

//======== Helper Functions =========================================

//======== Main Function ============================================

int main ()
{
    Example obj1;
    Example obj2;

    dump_instance ("Instance of obj1", obj1);
    obj1.printVars ();
    obj1.printFuncs ();

    printf ("\n");
    
    dump_instance ("Instance of obj2", obj2);
    obj2.printVars ();
    obj2.printFuncs ();

    return 0;
}

//======== Implementations ==========================================