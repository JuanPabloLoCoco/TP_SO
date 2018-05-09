#ifndef LIB_H
#define LIB_H

#include <stdint.h>

void * memset(void * destination, int32_t character, uint64_t length);
void * memcpy(void * destination, const void * source, uint64_t length);

char *cpuVendor(char *result);

extern void _halt();

#define MEMBEGIN 0x10000000
#define MAXMEMORY (128*1024*1024) //in b//
#define MINPAGE (4*1024) //in b//

#define PAGE_SIZE 4*1024

void readKeyboard(void);
void setup_IDT_entry (int index, uint64_t offset);
void timerTickHandler(void);
void setUPTimerTickHandler(void);

#endif
