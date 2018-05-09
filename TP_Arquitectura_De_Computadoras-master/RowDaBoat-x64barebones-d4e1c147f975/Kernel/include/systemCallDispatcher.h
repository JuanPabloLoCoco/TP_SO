#ifndef SYSTEM_CALLER_DISPATCHER_H
#define SYSTEM_CALLER_DISPATCHER_H

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
uint64_t sys_allocPage(uint64_t toAlloc);
uint64_t sys_free(uint64_t toFree);
uint64_t sys_leave();
uint64_t sys_ps(uint64_t buffer, uint64_t size);
uint64_t sys_sleep(uint64_t time);
uint64_t sys_yield();
uint64_t sys_exec(uint64_t entry_point, uint64_t pid, uint64_t cargs, uint64_t pargs);
uint64_t sys_kill(uint64_t pid, uint64_t msg);
uint64_t sys_myPID();
uint64_t sys_openPipe(uint64_t name,uint64_t ans);
uint64_t sys_closePipe(uint64_t name);
uint64_t sys_waitSemaphore(uint64_t semaphoreArg, uint64_t mutexArg);
uint64_t sys_signalSemaphore(uint64_t semaphoreArg);
uint64_t sys_initSemaphore(uint64_t semaphoreArg);
uint64_t sys_broadcastSemaphore(uint64_t semaphoreArg);
uint64_t sys_ipcs(uint64_t pipcs, uint64_t mutexes, uint64_t pipes, uint64_t ansMutexes, uint64_t ansPipes);
uint64_t sys_createMutex(uint64_t name, uint64_t mutex) ;
uint64_t sys_releaseMutex(uint64_t mutex,uint64_t ret) ;
uint64_t sys_tryLock(uint64_t mutex,uint64_t ret);
uint64_t sys_unlock(uint64_t mutex, uint64_t ret);
#endif
