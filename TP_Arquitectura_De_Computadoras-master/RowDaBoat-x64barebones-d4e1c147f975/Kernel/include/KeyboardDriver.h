#ifndef _KEYBOARD_DRIVER_H_
#define _KEAYBOARD_DRIVER_H_

#define SHIFT 0
#define CONTROL 1
#define ALT 2
#define CAPSLOCK 3
#define LSHIFTCODE 42
#define RSHIFTCODE 54
#define	CAPSLOCKCODE 58
#define BACKSPACECODE 14
#define NEWLINECODE 28
#define BUFFERSIZE 256

char getKey(void);
void incrementIndex(void);
void incrementRead(void);
int getChar(void);

#endif