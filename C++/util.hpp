/*
    Common helper functions
    Archive of Reversing.ID
*/
#include <cstdio>
#include <cstdint>

/*
    Dump isi dari memory di wilayah tertentu
    Digunakan oleh beberapa fungsi lain.
*/
template <typename T>
void dump_memory (T &t, int n, int width)
{
    uint8_t    counter = 16, padding;
    uint8_t  * v = reinterpret_cast<uint8_t*> (&t);

    while (n--) 
    {
        if (counter >= 16)
        {
            counter = 0;
            padding = width;
            printf ("\n");
            while (padding--) printf (" ");
        }

        printf (" %02x", *v++ & 0xFF);
        counter ++;
    }
}

/*
    Dump konten RTTI
*/
template <typename T>
void dump_rtti (T &t)
{
    /*
        Pointer menuju metadata RTTI berada tepat
        sebelum vtable.
    */
    // uintptr_t memiliki ukuran yang sama dengna ukuran pointer.
    uintptr_t * vptr   = reinterpret_cast<uintptr_t*> (&t);
    uintptr_t * vtable = reinterpret_cast<uintptr_t*> (*vptr);

    uintptr_t * meta_ptr = vtable - 1;
}

/*
    Dump konten vtable dari instance sebuah objek.

    Jika sebuah class memiliki virtual functions, maka byte awal
    dari instance adalah alamat menuju vtable.
    Disebut pula sebagai vtable pointer atau vptr.
*/
template <typename T>
void dump_vtable (T &t)
{
    // uintptr_t memiliki ukuran yang sama dengna ukuran pointer.
    uintptr_t * vptr   = reinterpret_cast<uintptr_t*> (&t);
    uintptr_t * vtable = reinterpret_cast<uintptr_t*> (*vptr);

    int idx;
    for (idx = 0; vtable[idx] != 0; idx++)
        printf ("     %p -> %p\n", vtable + idx, (void*) vtable[idx]); //reinterpret_cast<uintptr_t**> (vtable)[i]);

    printf ("vtable (%p) %d entr%s\n", 
        vtable, idx, ((idx == 1) ? "y" : "ies"));
}

/*
    Dump konten dari objek (class / struct)
*/
template <typename T>
void dump_instance (const char* header, T &t, bool vt = false, bool rtti = false)
{
    // ukuran ditentukan dari tipe data
    int n = sizeof (T);

    printf ("%s\n", header);
    printf ("[%p] -> instance (%zu bytes)", &t, sizeof (t));
    
    dump_memory (t, n, 2);

    if (vt)
    {
        printf ("\n\n");
        dump_vtable (t);
    }

    if (rtti)
    {
        printf ("\n\n");
        dump_rtti (t);
    }
    
    printf ("\n\n");
}