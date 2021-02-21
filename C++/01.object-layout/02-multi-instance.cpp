/*
    Multiple Instance (C++)
    Archive of Reversing.ID

Objective:
    Identifikasi tata letak memori (memory-layout) sebuah objek.
    Jika sebuah class memiliki dua atau lebih instance, dimana mereka berada?

Compile:
    (GCC)  
    $ g++ multi-instance.cpp -std=c++11 -o multi-instance
    
    (LLVM/Clang) 
    $ clang++ multi-instance.cpp -o multi-instance

    (MSVC)
    $ cl multi-instance.cpp

Run:
    $ multi-instance
*/

#include "../util.hpp"

/*
    Amati alamat setiap variabel dan fungsi

Pertanyaan:
    Variables
    - Apakah setiap instance memiliki variable dengan alamat sama?
    
    Functions
    - Apakah alamat fungsi dari setiap instance sama?    

Kesimpulan:
    Jika sebuah class memiliki banyak instance, setiap kelas akan memiliki 
    instance data masing-masing, namun fungsi (atau methods) yang 
    mengoperasikannya akan tetap sama.
*/

//======== Type Definitions =========================================

class Example
{
    int x;
    int y;
    int z;
public:
    Example () 
    {
        x = 135;
        y = 182;
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