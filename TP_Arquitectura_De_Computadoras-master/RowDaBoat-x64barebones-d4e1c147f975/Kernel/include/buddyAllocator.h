#ifndef BUDDYALLOCATOR_H
#define BUDDYALLOCATOR_H

#include "lib.h"

void initializeHeap();
void* buddyAllocatePages(uint64_t pages);
void* buddyAllocate(uint64_t amount);
uint16_t myBit(uint16_t n);
uint16_t myMask(uint16_t n);
int getMemoryUsed();

uint16_t recursiveMark(int index);
void* addNblocks(uint8_t  n);
void* recursiveAdd(int i, uint16_t n, uint64_t address, uint64_t innerSize);
void releaseUp(int i, uint16_t level);

int isInt(float f);
int buddyFree(void* address);
int searchMemoryUp(int i, uint16_t level);
int searchUp(int i, uint16_t level);
void releaseUp(int i,uint16_t level);


#define MAXHEAPSIZE (MAXMEMORY/MINPAGE)*2-1

#endif
