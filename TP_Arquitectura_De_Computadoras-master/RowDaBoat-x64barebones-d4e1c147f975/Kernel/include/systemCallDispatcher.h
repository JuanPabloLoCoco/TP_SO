#ifndef _SYSTEM_CALLER_DISPATCHER_H_
#define _SYSTEM_CALLER_DISPATCHER_H_


uint64_t sys_read(uint64_t fd, char* destination, uint64_t count);
uint64_t sys_write(unsigned int fd, const char* buffer, uint64_t count);
uint8_t sys_seconds(void);
uint8_t sys_mins(void);
uint8_t sys_hours(void);
uint32_t sys_year(void);
uint8_t sys_month(void);
uint8_t sys_day(void);
uint8_t getSeconds(void);
uint8_t getMinutes(void);
uint8_t getHours(void);
uint32_t getYear(void);
uint8_t getMonth(void);
uint8_t getDay(void);
uint64_t sys_paint(uint64_t x, uint64_t y);
uint64_t sys_clear(void);
uint64_t sys_drawCharPosition(uint64_t l,uint64_t x, uint64_t y);
uint64_t sys_getScreenInfo(uint64_t rdi);
uint64_t sys_setPointer(uint64_t x, uint64_t y);
uint64_t sys_ChangeColor(uint64_t blue,uint64_t green,uint64_t red);

#endif