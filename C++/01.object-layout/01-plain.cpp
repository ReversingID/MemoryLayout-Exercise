/*
    Plain Class (C++)
    Archive of Reversing.ID

Objective:
    Identifikasi tata letak memori (memory-layout) sebuah objek.
    Representasi dari sebuah class dengan tiga private-variable dan dua fungsi.

    Objek merupakan objek tanpa dekorasi dan polimorfisme, serta tidak memiliki
    relasi turunan (inheritance).

Compile:
    (GCC)  
    $ g++ plain.cpp -std=c++11 -o plain
    
    (LLVM/Clang) 
    $ clang++ plain.cpp -o plain

    (MSVC)
    $ cl plain.cpp

Run:
    $ plain
*/

#include "../util.hpp"

/*
    Amati alamat setiap variabel dan fungsi.

Pertanyaan:
    Variables
    Identifikasi variabel dan dapatkan alamatnya.
    - Apakah alamat dari setiap variabel saling berdekatan? 
    - Berapa ukuran setiap variabel?
    - Bandingkan urutan variabel di class serta di memory.
      Bagaimana urutannya?
    - Apakah letak variabel dekat dengan lokasi awal objek di memory?
    - Di segment apa variabel berada?
    
    Functions
    Identifikasi fungsi dan dapatkan alamatnya.
    - Apakah alamat dari setiap fungsi saling berdekatan?
    - Bandingkan urutan fungsi di class serta di memory.
      Bagaimana urutannya?
    - Apakah letak mereka dekat dengan lokasi awal objek di memory?
    - Apakah letak mereka dekat dengan variable?
    - Di segment apa fungsi-fungsi berada?
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
    Example kelas;

    dump_instance ("Plain Object without any decoration", kelas);
    kelas.printVars ();

    printf ("\n");
    kelas.printFuncs ();

    return 0;
}

//======== Implementations ==========================================