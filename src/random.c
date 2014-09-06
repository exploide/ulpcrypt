#include <stdio.h>

#ifdef _WIN32
    #include <windows.h>
#endif

#include "random.h"


/**
 * Fill an array with cryptographically secure (pseudo) random numbers, obtained from the OS.
 * The numbers are uniformly distributed over the interval [0, b).
 * @param uint64_t buffer[] - the array to fill with random numbers
 * @param size_t count - number of random numbers to retrieve
 * @param uint64_t b - bound for sampling
 * @return int - 0 on success, a negative value otherwise
 */
int get_random_numbers(uint64_t buffer[], size_t count, uint64_t b) {

    #ifdef __linux__

        uint64_t bad = UINT64_MAX - (UINT64_MAX % b);
        FILE* f = fopen("/dev/urandom", "r");
        if(f == NULL)
            return -1;
        int err = 0;
        err += count - fread(buffer, sizeof(uint64_t), count, f);
        for(size_t i = 0; i < count; i++) {
            while(buffer[i] >= bad) {
                err += 1 - fread(&(buffer[i]), sizeof(uint64_t), 1, f);
            }
            buffer[i] %= b;
        }
        err -= fclose(f);
        return -err;

    #elif _WIN32

        uint64_t bad = UINT64_MAX - (UINT64_MAX % b);
        HMODULE hmod = LoadLibrary("advapi32.dll");
        if(hmod == NULL)
            return -1;
        BOOLEAN (APIENTRY* RtlGenRandom_ptr)(PVOID, ULONG) = (BOOLEAN (APIENTRY*)(PVOID, ULONG)) GetProcAddress(hmod, "SystemFunction036");
        if(!RtlGenRandom_ptr) {
            FreeLibrary(hmod);
            return -1;
        }
        int err = 0;
        if(!RtlGenRandom_ptr(buffer, count * sizeof(uint64_t)))
            err++;
        for(size_t i = 0; i < count; i++) {
            while(buffer[i] >= bad) {
                if(!RtlGenRandom_ptr(&(buffer[i]), sizeof(uint64_t)))
                    err++;
            }
            buffer[i] %= b;
        }
        if(!FreeLibrary(hmod))
            err++;
        return -err;

    #endif

}
