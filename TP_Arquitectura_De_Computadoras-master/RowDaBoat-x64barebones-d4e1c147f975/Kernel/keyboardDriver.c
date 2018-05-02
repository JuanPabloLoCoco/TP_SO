#include <naiveConsole.h>
#include <lib.h>
#include <videoDriver.h> 
#include <KeyboardDriver.h>
#include <KeyboardMap.h>
#include <time.h>

int isAlpha(char);
static int count = 0;
static uint8_t status = 0;
uint8_t buffer[BUFFERSIZE];
uint16_t index = 0;
uint16_t read = 0;

void keyboard_handler() {
	char l = getKey();
	if(l >0) {
		if(kbdus[l]) {
			count++;
			if(status & 1<<SHIFT){
				buffer[index] = shiftedkey[l];
			}
			else if(status & 1<<CAPSLOCK){
				buffer[index] = capsKey[l];
			}
			else
				buffer[index] = kbdus[l];
			incrementIndex();
		}
		else {
			if(l == LSHIFTCODE || l == RSHIFTCODE)  //shift pressed
				status = status | 1<<SHIFT;
			else if(l == CAPSLOCKCODE) {  //caps pressed
				if(status & 1<<CAPSLOCK)
					status = status & (~(1<<CAPSLOCK));
				else
					status = status | 1<<CAPSLOCK;		
			}
			else if(l == BACKSPACECODE) {
				buffer[index] = '\b';
				incrementIndex();
				if(count > 0){
					count--;
					erase_char();
				}

			}
			else if(l == NEWLINECODE){
				buffer[index] = '\n';
				incrementIndex();
				count = 0;
			}
		}	
	}
	else {
	 	if(l+128 == LSHIFTCODE || l+128 == RSHIFTCODE) //shift removed
			status = status & (~(1<<SHIFT));

	}
}

void incrementIndex(){
	if((index + 1 %256) != read) {
		index ++;
		index = index%256;
	}
}

void incrementRead(){
	if(read != index){
		read ++;
		read = read % 256;
	}
}

int getChar() {
	_sti();
	if(read == index)
		return -1;
	int c = buffer[read];
	incrementRead();
	return c;
}