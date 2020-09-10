// 10th of September 2020
// by Duchy
#include <stdio.h>

#ifdef _WIN32 
    #include <windows.h>
    #include <intrin.h>
    #pragma intrinsic(__rdtsc)
#elif __linux__
    #ifndef __clang__
        /* 
         * proudly ripped and edited from 
         * https://web.archive.org/web/20180916070251/http://www.mcs.anl.gov/~kazutomo/rdtsc.html
         */
        #ifdef __i386__
        static __inline__ unsigned long long __rdtsc(void)
        {
            unsigned long long int x;
            __asm__ __volatile__ (".byte 0x0f, 0x31" : "=A" (x));
            return x;
        }
        #elif __x86_64__
        static __inline__ unsigned long long __rdtsc(void)
        {
            unsigned hi, lo;
            __asm__ __volatile__ ("rdtsc" : "=a" (lo), "=d" (hi));
            return ( (unsigned long long)lo)|( ((unsigned long long)hi)<<32 );
        }
        #endif
    #endif
#endif



int main()
{
    unsigned long long time1, time2, sum = 0;
    const unsigned char avg = 100;
    
    for (int i = 0; i < avg; i++){
        time1 = __rdtsc();
#ifdef _WIN32
        __asm cpuid;
#elif __linux__
        __asm__("cpuid");
#endif
        time2 = __rdtsc();
        sum += time2 - time1;
    }

    sum = sum / avg;
    printf("%llu\n", sum);

    if(sum > 500){
        puts("Probably a VM");
    }else{
        puts("Probably Bare-Metal");
    }
    
    return 0;
}
