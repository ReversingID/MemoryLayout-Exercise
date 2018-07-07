/*
Identifikasi tata letak memori (memory-layout) sebuah objek.
Apakah urutan deklarasi memengaruhi representasi objek di memory?

Compile:
    (GCC)  
    $ g++ permutate-layout.cpp -std=c++11 -o permutate-layout

    (LLVM)
    $ clang++ permutate-layout.cpp -o permutate-layout

    (MSVC)
    $ cl permutate-layout.cpp

Run:
    $ permutate-layout
*/
#include "../util.hpp"
#include <cstddef>

/*
Alamat memory adalah angka-angka yang menunjukkan posisi di memory dimana data
berada. Processor dapat membaca data pada alamat berapa saja, namun untuk akses
yang optimal, data diletakkan di alamat dengan kelipatan tertentu. Data dengan
ukuran sembarang akan kemungkinan disediakan ruang sebanyak kelipatan angka 
yang diatur. Pengaturan tata letak ini diakukan secara otomatis oleh compiler.

Amati alamat setiap variabel dan fungsi.
Pertanyaan:
    - Apakah setiap variabel menempati alamat dengan kelipatan tertentu?
      Berapa?
    - Bandingkan jarak antar variabel dengan ukuran seharusnya variabel.
      Apakah berbeda ataukah sama?
    - Mengapa Example1 dan Example2 berbeda dengan Example3 ? 
      Sementara Example1 dan Example2 memiliki ukuran yang sama?
    - Mengapa Example4 dan Example5 memiliki ukuran yang berbeda?
    - Apa konten dari padding yang ada? Random atau memiliki nilai tertentu?
      Bagaimana memastikannya?
    - Adakah alignment lain selain yang ditemukan di poin pertama?

Kesimpulan:
    Menempatkan atau memosisikan variabel dalam urutan tertentu akan memengaruhi 
    ukuran. Setiap variabel struct atau class harus selalu diposisikan sesuai 
    alignment, dengan demikian compiler akan akan memberikan padding jika diperlukan.
*/

//======== Type Definitions =========================================
// Size: 16 = 4 + 10 + 2
struct Example1
{
    int32_t x;
    int8_t  y[10];
    int16_t z;
};

// Size: 16 = 4 + 2 + 10
struct Example2
{
    int32_t x;
    int16_t y;
    int8_t  z[10];
};

// Size: 20 = 10 (+2 padding) + 4 + 2
// 10 byte awal (x) akan dipaksa untuk menjadi kelipatan 4
struct Example3
{
    int8_t  x[10];
    int32_t y;
    int16_t z;
};

// Size: 16 = 1 + 8 kemudian dibulatkan menjadi kelipatan 8
struct Example4
{
    int8_t x;
    int64_t y;
};

// Size: 8 = 4 + 1 kemudian dibulatkan menjadi kelipatan 4
struct Example5
{
    int32_t x;
    int8_t  y;
};

//======== Helper Functions =========================================
template<typename T>
void dump_variables(T &t);

//======== Main Function ============================================
int main()
{
    Example1 ex1;
    Example2 ex2;
    Example3 ex3;

    dump_instance("Instance of Example1", ex1);
    dump_variables(ex1);

    printf("\n-------------------------\n\n");

    dump_instance("Instance of Example2", ex2);
    dump_variables(ex2);

    printf("\n-------------------------\n\n");
    
    dump_instance("Instance of Example3", ex3);
    dump_variables(ex3);

    printf("\n-------------------------\n\n");

    printf("Sizeof(Example4) = %d\n", sizeof(Example4));
    printf("Sizeof(Example5) = %d\n", sizeof(Example5));

    return 0;
}

//======== Implementations ==========================================
template<typename T>
void dump_variables(T &t)
{
    // Trik mencetak offset:
    // (int) offsetof(ClassName,field)
    printf("Address of x: [%p] +%d\n", &t.x, (size_t)offsetof(T,x));
    printf("Address of y: [%p] +%d\n", &t.y, (size_t)offsetof(T,y));
    printf("Address of z: [%p] +%d\n", &t.z, (size_t)offsetof(T,z));
}