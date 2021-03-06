#include "include/buddyAllocator.h"
#include "include/videoDriver.h"
#include "include/lib.h"
#include "include/mutex.h"
#include "include/scheduler.h"
#include "include/math.h"
#include "include/defs.h"

#define PARENT(i) ((i) >> 1)
#define LCHILD(i) ((i) << 1)
#define RCHILD(i) (((i) << 1) + 1)
#define AMILEFT(i) !((i) % 2)
#define ISNAVAILABLE(i,n) ((i)&(myBit(n)))

static uint16_t heap[MAXHEAPSIZE];
static uint64_t heapSize;
static uint64_t block;
static void* beginning = (void*) MEMBEGIN;
static int mutex;

void* buddyAllocate(uint64_t amount)
{
    if(amount<=0) return NULL;

    lockMutex(mutex);

    uint64_t pages = roundUpPower2(amount/block);
    pages = pages == 0 ? 1 : pages;
    void* ans = addNblocks(pages);

    unlockMutex(mutex);

    return ans;
}

void* buddyAllocatePages(uint64_t pages)
{
    if (pages==0) return NULL;

    lockMutex(mutex);

    void* ans=addNblocks(pages);

    unlockMutex(mutex);

    return ans;
}


uint16_t myBit(uint16_t n)
{
    int i = 0;
    while(n)
    {
        n = n >> 1;
        i++;
    }
    return 1 << (i - 1);
}

uint16_t myMask(uint16_t n)
{
    uint16_t i = 0;
    while(n)
    {
        n--;
        i = (i << 1) + 1;
    }
    return i;
}

void initializeHeap()
{
    mutex = getMutex(PAGESMUTEX);
    block = MINPAGE;
    heapSize = MAXHEAPSIZE;
    recursiveMark(1);
}

uint16_t recursiveMark(int index)
{
    if(index > heapSize/2)
    {
        heap[index] = 1;
        return (1 << 1) + 1;
    }

    recursiveMark(RCHILD(index));
    uint16_t mark = recursiveMark(LCHILD(index));
    heap[index] = mark;
    return (mark << 1) + 1;
}

void* addNblocks(unsigned char  n)
{
    int a = ((1 + heapSize)/2);

    if(n > ((1 + heapSize)/2)) return NULL;

    return recursiveAdd(1, n, (uint64_t)beginning, MAXMEMORY);
}

void* recursiveAdd(int i, uint16_t n, uint64_t address, uint64_t innerSize)
{
    void*ans = NULL;
    if(!ISNAVAILABLE(heap[i], n))
    {
        return NULL;
    }
    else
    {
        if(i <= heapSize/2 && ISNAVAILABLE(heap[RCHILD(i)], n))
        {
            ans= recursiveAdd(RCHILD(i), n, address + (innerSize/2), innerSize/2);
            heap[i] = heap[RCHILD(i)] | heap[LCHILD(i)];
        }
        else if(i <= heapSize/2 && ISNAVAILABLE(heap[LCHILD(i)], n))
        {
            ans = recursiveAdd(LCHILD(i),n,address,innerSize/2);
            heap[i] = heap[RCHILD(i)] | heap[LCHILD(i)];
        }
        else
        {
            heap[i] = 0;
            return (void*)address;
        }
    }
    return ans;
}

int isInt(float f)
{
    return (f-(int)f == 0);
}

int buddyFree(void* address)
{
    int ans;

    lockMutex(mutex);

    address = (void*)((char*)address - (char*)beginning);
    if(!isInt((uint64_t)address/(block*1.0f)))
    {
        ans = -1;
    }
    else
    {
        int position = ((uint64_t)address)/block;
        ans = searchUp(heapSize/2 + 1 + position,1);
    }

    unlockMutex(mutex);

    return ans;
}


int searchMemoryUp(int i, uint16_t level)
{
    if(i < 1) return 0;
    if(heap[i] == 0)
    {
        return pow2(level-1);
    }
    else if(AMILEFT(i))
    {
        return searchMemoryUp(PARENT(i), level+1);
    }
    else
    {
        return 0;
    }
}


int getMemoryUsed()
{
    int acu = 0;
    for (int i = heapSize/2 + 1; i < MAXHEAPSIZE; ++i)
    {
        acu += searchMemoryUp(i,1);
    }
    return acu * MINPAGE;
}

int searchUp(int i, uint16_t level)
{
    if(i < 1) return -1;
    if(heap[i] == 0)
    {
        heap[i] = myMask(level);
        releaseUp(PARENT(i), level+1);
        return 0;
    }
    else if(AMILEFT(i))
    {
        return searchUp(PARENT(i), level+1);
    }
    else
    {
        return -1;
    }
}

void releaseUp(int i,uint16_t level)
{
    if(i < 1) return;
    if(heap[RCHILD(i)] == myMask(level-1) && heap[LCHILD(i)] == myMask(level-1))
    {
        heap[i] = myMask(level);
    }
    else
    {
        heap[i] = heap[RCHILD(i)] | heap[LCHILD(i)];
    }
    releaseUp(PARENT(i), level+1);
}
