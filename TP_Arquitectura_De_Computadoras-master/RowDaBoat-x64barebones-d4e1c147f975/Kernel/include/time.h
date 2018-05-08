#ifndef TIME_H
#define TIME_H

void timer_handler(void);
int ticks_elapsed(void);
int seconds_elapsed(void);
int resetTicks(void);
int getSeconds(void);
int getMinutes(void);
int getHours(void);
int getYear(void);
int getMonth(void);
int getDay(void);


void deleteSleep(int index);
void addSleep(int pid,int interval);
void doneSleeping(int index);
void sleep(unsigned int time);

void executeSchedule();
void activateScheduler();

void addTimerListener(timerEventT event, int interval);
void deleteTimerListener(timerEventT event);

#endif
