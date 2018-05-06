#ifndef BUDDYALLOCATOR_H
#define BUDDYALLOCATOR_H

#include "lib.h"

void initializeHeap();
void* buddyAllocatePages(uint64_t pages);
void* buddyAllocate(uint64_t amount);
int buddyFree(void* address);
uint16_t myBit(uint16_t n);
uint16_t myMask(uint16_t n);
int isPowerOfTwo (uint64_t x);
uint64_t roundUpPower2(uint64_t v);

int getMemoryUsed();


#define MAXHEAPSIZE (MAXMEMORY/MINPAGE)*2-1

#endif //BUDDYALLOCATOR_H
