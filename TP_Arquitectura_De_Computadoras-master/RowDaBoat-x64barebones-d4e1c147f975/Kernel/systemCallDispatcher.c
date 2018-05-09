#include <stdint.h>
#include <videoDriver.h>
#include <systemCallDispatcher.h>
#include <buddyAllocator.h>
#include <scheduler.h>
#include <time.h>
#include <semaphore.h>
#include <mutex.h>



uint64_t systemCallDispatcher(uint64_t rax, uint64_t rdi, uint64_t rsi, uint64_t rdx, uint64_t r8, uint64_t r9)
{
		uint64_t result;
		switch(rax)
		{
			case 0:
				result = sys_read(rdi, rsi, rdx);
				break;
			case 1:
				 result = sys_write(rdi, rsi, rdx);
				 break;
			case 2:
				result =(uint64_t)sys_seconds();
				break;
			case 3:
				result=(uint64_t)sys_mins();
				break;
			case 4:
				result =(uint64_t)sys_hours();
				break;
			case 5:
				result = sys_year();
				break;
			case 6:
				result = sys_month();
				break;
			case 7:
				result =  sys_day();
				break;
			case 8:
				result =  sys_paint(rdi, rsi);
				break;
			case 9:
				result =  sys_clear();
				break;
			case 10:
				result =  sys_drawCharPosition(rdi, rsi, rdx);
				break;
			case 11:
				result =  sys_getScreenInfo(rdi);
				break;
			case 12:
				result =  sys_setPointer(rdi, rsi);
				break;
			case 13:
				result = sys_ChangeColor(rdi, rsi, rdx);
				break;
			case 14:
				result = sys_allocPage(rdi);
				break;
			case 15:
				result = sys_free(rdi);
				break;
			case 16:
				result = sys_leave();
				break;
			case 17:
				result = sys_ps(rdi, rsi);
				break;
			case 18:
				result = sys_sleep(rdi);
				break;
			case 19:
				result = sys_yield();
				break;
			case 20:
				result = sys_exec(rdi, rsi,rdx, r8);
				break;
			case 21:
				result = sys_kill(rdi, rsi);
				break;
			case 22:
				result = sys_myPID();
				break;
			case 23:
				result = sys_openPipe(rdi,rsi);
				break;
			case 24:
				result = sys_closePipe(rdi);
				break;
			case 25:
				result = sys_signalSemaphore(rdi);
				break;
			case 26:
				result = sys_waitSemaphore(rdi,rsi);
				break;
			case 27:
				result = sys_initSemaphore(rdi);
				break;
			case 28:
				result = sys_broadcastSemaphore(rdi);
				break;
			case 29:
				result = sys_ipcs(rdi,rsi,rdx,r8,r9);
				break;
			case 30:
				result = sys_createMutex(rdi,rsi);
				break;
			case 31:
				result = sys_releaseMutex(rdi, rsi);
				break;
			case 32:
				result = sys_tryLock(rdi,rsi);
				break;
			case 33:
				result = sys_unlock(rdi,rsi);
				break;
		}
		return result;
}

uint64_t sys_read(uint64_t fd, char* destination, uint64_t count)
{
	uint64_t i = 0;
	int c = 0;
  if (fd == 0)
	{
		while (i < count)
		{
			c = getChar();
			if(c != -1)
			{
				destination[i] = c;
				i++;
			}
		}
  }
  return i;
}

uint64_t sys_write(unsigned int fd, const char* buffer, uint64_t count)
{
	int i = 0;
	if(fd == 1)
	{
		while(i < count)
		{
			if(buffer[i] == '\n')
				newLine();
			else
				draw_char(buffer[i]);
			i++;
		}
	}
	return i;
}

uint8_t sys_seconds()
{
	uint8_t seconds = getSeconds();
	return seconds;
}


uint8_t sys_mins()
{
	uint8_t minutes = getMinutes();
	return minutes;
}

uint8_t sys_hours()
{
	uint8_t hours = getHours();
	return hours;
}


uint32_t sys_year()
{
	uint32_t year = getYear();
	return year;
}


uint8_t sys_month()
{
	uint8_t month = getMonth();
	return month;
}

uint8_t sys_day()
{
	uint8_t day = getDay();
	return day;
}


uint64_t sys_paint(uint64_t x, uint64_t y)
{
	draw_pixel(x,y);
	return 0;
}

uint64_t sys_clear()
{
	cls();
	return 0;
}


uint64_t sys_drawCharPosition(uint64_t l, uint64_t x, uint64_t y)
{
	draw_char_position(l, x, y);
	return 0;
}

uint64_t sys_getScreenInfo(uint64_t rdi)
{
	switch(rdi)
	{
		case 0:
			return getScreenWidth();
		case 1:
			return getScreenHeigth();
	}
	return 0;
}

uint64_t sys_setPointer(uint64_t x, uint64_t y)
{
	setPointer(x,y);
	return 0;
}

uint64_t sys_ChangeColor(uint64_t blue,uint64_t green,uint64_t red)
{
	setFontColor(blue,green,red);
	return 0;
}

uint64_t sys_allocPage(uint64_t toAlloc)
{
 	void* address = buddyAllocate(toAlloc);
	return (uint64_t) address;
}

uint64_t sys_free(uint64_t toFree)
{
 	buddyFree(toFree);
	return 0;
}

uint64_t sys_leave()
{
	if (getForegroundPid() == getCurrentPid())
	{
  	setForeground(1); // give forground to shell
  }
  changeProcessState(getCurrentPid(), DEAD);
  _yield();
  return 0;
}

uint64_t sys_ps(uint64_t buffer, uint64_t size)
{
	sprintAllProcesses(buffer, size);
  return 0;
}

uint64_t sys_sleep(uint64_t time)
{
	sleep(time);
  return 0;
}

uint64_t sys_yield()
{
    _yield();
    return 0;
}

uint64_t sys_exec(uint64_t entry_point, uint64_t pid, uint64_t cargs, uint64_t pargs)
{
    int * retPid = (int *) pid;
    *retPid = insertProcess((void *)entry_point, (int)cargs, (void **)pargs);
    return 0;
}

uint64_t sys_kill(uint64_t pid, uint64_t msg)
{
    switch(msg)
		{
        case 0:
            // kill custom process
            changeProcessState(pid, DEAD);
            break;
        case 1:
            // sleep custom process
            changeProcessState(pid, SLEEPING);
            break;
        case 2:
            // wake up custom process
            changeProcessState(pid, READY);
            break;
        case 3:
            setForeground(pid);
            break;
    }
    return 0;
}

uint64_t sys_myPID()
{
    // int * retPid = (int *) ans;
    // *retPid = getCurrentPid();
    return getCurrentPid();
}

uint64_t sys_openPipe(uint64_t name,uint64_t ans) {
  	int * a = (int *) ans;
  	*a = addPipe(getPipe((char*)name)) +3;
  	return 0;
}

uint64_t sys_closePipe(uint64_t name) {
    releasePipe(name);
    return;
}

uint64_t sys_waitSemaphore(uint64_t semaphoreArg, uint64_t mutexArg)
{
    semaphore_t * semaphore = (semaphore_t *) semaphoreArg;
    int mutex = (int ) mutexArg;
    waitSemaphore(semaphore,mutex);
		return 0;
}

uint64_t sys_signalSemaphore(uint64_t semaphoreArg)
{
    semaphore_t * semaphore = (semaphore_t *) semaphoreArg;
    signalSemaphore(semaphore);
    return;
}

uint64_t sys_initSemaphore(uint64_t semaphoreArg)
{
    semaphore_t * semaphore = (semaphore_t *) semaphoreArg;
    initSemaphore(semaphore);
    return;
}

uint64_t sys_broadcastSemaphore(uint64_t semaphoreArg)
{
    semaphore_t * semaphore = (semaphore_t *) semaphoreArg;
    broadcastSemaphore(semaphore);
    return;
}

uint64_t sys_ipcs(uint64_t pipcs, uint64_t mutexes, uint64_t pipes,uint64_t ansMutexes,uint64_t ansPipes)
{
    int *ansM = (int *) ansMutexes;
    int *ansP = (int *) ansPipes;
    ipcs *ans = (ipcs *) pipcs;
    *ansM = getMuxeseNames(ans, mutexes);
    *ansP = getPipesNames(ans, pipes);
    return;
}


/*------------------------MUTEX ----------------------*/
uint64_t sys_createMutex(uint64_t name, uint64_t mutex)
{
    int * ret = (int *) mutex;
    *ret = getMutex((char*) name);
    return 0;
}

uint64_t sys_releaseMutex(uint64_t mutex,uint64_t ret)
{
    int * retVal = (int *) ret;
    int mutexCode = (int ) mutex;
    *retVal = releaseMutexFromPos(mutexCode);
    return 0;
}


uint64_t sys_tryLock(uint64_t mutex,uint64_t ret)
{
    int * retVal = (int *) ret;
    int mutexCode = (int ) mutex;
    *retVal = lockMutex(mutexCode);
    return 0;
}

uint64_t sys_unlock(uint64_t mutex, uint64_t ret)
{
    int * retVal = (int *) ret;
    int mutexCode = (int ) mutex;
    *retVal = unlockMutex(mutexCode);
    return 0;
}
