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

#endif
