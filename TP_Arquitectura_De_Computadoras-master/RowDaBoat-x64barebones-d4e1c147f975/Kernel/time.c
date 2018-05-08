#include <time.h>
#include <naiveConsole.h>
#include <mutex.h>
#include <process.h>
#include <scheduler.h>

#define MAX_LISTENERS 50

extern void _change_process();

static unsigned long ticks = 0;

static int timerListeners =0;
static int sleepListeners =0;
static int auxj=0;

static timerEventT timerEvents[MAX_LISTENERS];
static int alarmEvents[MAX_LISTENERS];

static int sleepPIDS[MAX_LISTENERS];
static int sleepTicks[MAX_LISTENERS];
static int alarmSleep[MAX_LISTENERS];



void timer_handler()
{
	ticks++;
	// for (auxj = 0; auxj < timerListeners; auxj++)
	// {
	// 	if(ticks % alarmEvents[auxj]==0) timerEvents[auxj]();
	// }
	// for(auxj=0;auxj < sleepListeners; auxj++)
	// {
	// 	sleepTicks[auxj]+=1;
	// 	if(sleepTicks[auxj] == alarmSleep[auxj])
	// 	{
	// 		doneSleeping(auxj);
  //     auxj--;
	// 	}
	// }
	// executeSchedule();
}

void deleteSleep(int index)
{
	if(index >= sleepListeners) return;

	lockScheduler();

	alarmSleep[index] = alarmSleep[sleepListeners-1];
	sleepPIDS[index] = sleepPIDS[sleepListeners-1];
	sleepTicks[index] = sleepTicks[sleepListeners-1];
  sleepListeners--;

	unlockScheduler();
}

void addSleep(int pid,int interval)
{
	if(sleepListeners >= MAX_LISTENERS) return;

	lockScheduler();

	alarmSleep[sleepListeners] = interval;
	sleepPIDS[sleepListeners] = pid;
	sleepTicks[sleepListeners] = 0;
	sleepListeners++;

	unlockScheduler();
}

void doneSleeping(int index)
{
	changeProcessState(sleepPIDS[index],READY);
	deleteSleep(index);
}

void sleep(unsigned int time)
{
	char myPid = getCurrentPid();
  addSleep(myPid,time);
	changeProcessState(myPid,SLEEPING);
  _yield();
	return;
}

void executeSchedule()
{
	_change_process();
}

void activateScheduler() {
	addTimerListener(&executeSchedule, 1);
}

void addTimerListener(timerEventT event, int interval)
{
	_cli();
	if(timerListeners >= MAX_LISTENERS) return;
	else
	{
		alarmEvents[timerListeners] = interval;
		timerEvents[timerListeners] = event;
		timerListeners++;
 	}
	_sti();
}

void deleteTimerListener(timerEventT event)
{
	_cli();
	for (int j = 0; j < timerListeners; j++)
	{
		if(timerEvents[j]==event)
		{
			for(int k=j;k<timerListeners-1;k++)
			{
				timerEvents[k]=timerEvents[k+1];
				alarmEvents[k]=alarmEvents[k+1];
			}
			timerListeners--;
			break;
		}
	}
	_sti();
}

int ticks_elapsed()
{
	return ticks;
}

int seconds_elapsed()
{
	return ticks / 18;
}

int resetTicks()
{
	ticks = 0;
}
