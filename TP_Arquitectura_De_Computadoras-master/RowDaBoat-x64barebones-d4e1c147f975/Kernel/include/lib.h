#ifndef LIB_H
#define LIB_H

#include <stdint.h>

void * memset(void * destination, int32_t character, uint64_t length);
void * memcpy(void * destination, const void * source, uint64_t length);

char *cpuVendor(char *result);

int getSeconds(void);

int getMinutes(void);

int getHours(void);

int getYear(void);

int getMonth(void);

int getDay(void);

void readKeyboard(void);

void setup_IDT_entry (int index, uint64_t offset);

void timerTickHandler(void);

void setUPTimerTickHandler(void); 


#endif