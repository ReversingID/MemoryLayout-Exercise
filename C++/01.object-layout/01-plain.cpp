/*
Identifikasi tata letak memori (memory-layout) sebuah objek.
Representasi dari sebuah class dengan tiga private-variable dan dua fungsi.

Plain object, objek tanpa adanya dekorasi serta merupakan objek tunggal tanpa
adanya relasi turunan (inheritance).

Compile:
    (GCC)  
    $ g++ plain.cpp -std=c++11 -o plain
    
    (LLVM) 
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
    - Apakah alamat dari setiap variabel saling berdekatan? Lihat pula ukurannya.
    - Apakah alamat mereka membentuk sebuah urutan? Bagaimana urutannya?
    - Apakah letak mereka dekat dengan lokasi awal objek di memory?
    - Di segment apa variabel berada?
    
    Functions
    - Apakah alamat dari seetiap fungsi saling berdekatan? Mengapa?
    - Apakah alamat mereka membentuk sebuah urutan? Bagaimana urutannya?
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
    Example() 
    {
        x = 135;
        y = 182;
    }
    void printVars()
    {
        printf("Location x: [%p] | Value: %d\n", &x, x);
        printf("Location y: [%p] | Value: %d\n", &y, y);
        printf("Location z: [%p] | Value: %d\n", &z, z);
    }
    void printFuncs()
    {
        printf("Location of printVars   : [%p]\n", &Example::printVars);
        printf("Location of printFuncs  : [%p]\n", &Example::printFuncs);
    }
};

//======== Helper Functions =========================================

//======== Main Function ============================================
int main()
{
    Example kelas;

    dump_instance("Plain Object without any decoration", kelas);
    kelas.printVars();

    printf("\n");
    kelas.printFuncs();

    return 0;
}

//======== Implementations ==========================================