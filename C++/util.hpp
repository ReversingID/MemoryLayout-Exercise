/*
Common helper functions.
*/
#include <cstdio>
#include <cstdint>

/**
 * Dump isi dari memory di wilayah tertentu
 * Digunakan oleh beberapa fungsi lain.
 */
template <typename T>
void dump_memory(T &t, int n, int width)
{
    uint8_t    counter = 16, padding;
    uint8_t  * v = reinterpret_cast<uint8_t*>(&t);

    while (n--) 
    {
        if (counter >= 16)
        {
            counter = 0;
            padding = width;
            printf("\n");
            while (padding--) printf(" ");
        }

        printf(" %02x", *v++ & 0xFF);
        counter ++;
    }
}

/**
 * Dump konten vtable dari instance sebuah objek.
 */
template <typename T>
void dump_vtable(T &t, int virtuals, bool rtti)
{
    // Jika sebuah class memiliki virtual functions, maka
    // byte-byte awal dari instance adalah alamat menuju vtable.
    // Disebut pula vtable pointer atau vptr.
    uintptr_t * vptr   = reinterpret_cast<uintptr_t*>(&t);
    uintptr_t * vtable = reinterpret_cast<uintptr_t*>(*vptr);

    printf("vtable (%08x) %d entr%s\n", 
        vtable,
        virtuals, 
        ((virtuals == 1) ? "y" : "ies"));

    for (int i = 0; i < virtuals; i++)
        printf("     %08x -> %08x\n", vtable + i, vtable[i]); //reinterpret_cast<uintptr_t**>(vtable)[i]);
    
    if (rtti)
    {
        printf("\n\n");
        dump_rtti(vtable);
    }
}

/** 
 * Dump konten dari objek (class / struct)
 */
template <typename T>
void dump_instance(const char* header, T &t, int virtuals = 0, bool rtti = false)
{
    int n = sizeof(t);

    printf("%s\n", header);
    printf("[%08x] -> instance (%d bytes)", &t, sizeof(t));
    
    dump_memory(t, n, 2);
    if (virtuals > 0)
    {
        printf("\n\n");
        dump_vtable(t, virtuals, rtti);
    }
    
    printf("\n\n");
}