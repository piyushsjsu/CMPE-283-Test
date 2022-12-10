#include <stdio.h>
#include <sys/types.h>

// Referred from https://www.spinics.net/lists/linux-tip-commits/msg61284.html

static inline void __cpuid(unsigned int *eax,
 			unsigned int *ebx,
 			unsigned int *ecx,
 			unsigned int *edx)
{
 	asm volatile("cpuid": "=a" (*eax),"=b" (*ebx),"=c" (*ecx),"=d" (*edx): "0" (*eax), "1" (*ebx), "2" (*ecx), "3" (*edx));
}

int main(int argc, char **argv)
{
	unsigned int eax, ebx, ecx, edx;
	unsigned long long cycle_time;

	eax = 0x4FFFFFFC;
	__cpuid(&eax, &ebx, &ecx, &edx);
	printf("CPUID(0x4FFFFFFC), Total exits  : %u \n", eax);

	eax = 0x4FFFFFFD;
	__cpuid(&eax, &ebx, &ecx, &edx);
	cycle_time = (unsigned long long) ebx << 32 | ecx;
	printf("CPUID(0x4FFFFFFD), Total time in VMM : %llu cycles \n", cycle_time);
	
	unsigned int temp;
	    printf("\n-------------------------------------(0x4FFFFFFE)------------------------------------------------\n\n");
    for (int i = 0; i < 75; i++) {
        eax = 0x4FFFFFFE;
        ecx = i;
        temp = ecx;
        __cpuid(&eax, &ebx, &ecx, &edx);
        printf("CPUID(0x4FFFFFFE), Exit no: %u --> Total Exits: %u \n", temp, eax);
    }

    printf("\n-------------------------------------(0x4FFFFFFF)------------------------------------------------\n\n");
    for (int i = 0; i < 75; i++) {
        eax = 0x4FFFFFFF;
        ecx = i;
        temp = ecx;
        __cpuid(&eax, &ebx, &ecx, &edx);
        cycle_time = (unsigned long long) ebx << 32 | ecx;
        printf("CPUID(0x4FFFFFFF), Exit no: %u --> Total time in VMM: %llu \n", temp, cycle_time);
    }
}
