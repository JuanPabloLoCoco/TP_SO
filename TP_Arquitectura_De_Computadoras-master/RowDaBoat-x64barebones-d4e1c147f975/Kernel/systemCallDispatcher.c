#include <stdint.h>
#include <videoDriver.h>
#include <systemCallDispatcher.h>

uint64_t systemCallDispatcher(uint64_t rax, uint64_t rdi, uint64_t rsi, uint64_t rdx, uint64_t r8, uint64_t r9) {
		uint64_t result;
		switch(rax) {
			case 0:
				result =sys_read(rdi,rsi,rdx);
			case 1:
				 result = sys_write(rdi,rsi,rdx);
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
				result =  sys_paint(rdi,rsi);
				break;
			case 9:
				result =  sys_clear();
				break;
			case 10:
				result =  sys_drawCharPosition(rdi,rsi,rdx);
				break;
			case 11:
				result =  sys_getScreenInfo(rdi);
				break;
			case 12:
				result =  sys_setPointer(rdi,rsi);
				break;
			case 13:
				result = sys_ChangeColor(rdi,rsi,rdx);
				break;
		}
		
		return result;
}

uint64_t sys_read(uint64_t fd, char* destination, uint64_t count){
	
	uint64_t i = 0;
	int c = 0;
    if (fd == 0) {
		while (i < count) {
			c = getChar();
			if(c != -1){
				destination[i] = c;
				i++;
			}
		}
    }
    return i;
}

uint64_t sys_write(unsigned int fd, const char* buffer, uint64_t count) {
	int i = 0;
	if(fd == 1){
		while(i<count){
			if(buffer[i] == '\n')
				newLine();
			else
				draw_char(buffer[i]);
			i++;
		}
	}
	return i;
}

uint8_t sys_seconds(){
	uint8_t seconds = getSeconds();
	return seconds;
}


uint8_t sys_mins(){
	uint8_t minutes = getMinutes();
	return minutes;
}

uint8_t sys_hours(){
	uint8_t hours = getHours();
	return hours;
}


uint32_t sys_year(){
	uint32_t year = getYear();
	return year;
}


uint8_t sys_month(){
	uint8_t month = getMonth();
	return month;
}

uint8_t sys_day(){
	uint8_t day = getDay();
	return day;
}


uint64_t sys_paint(uint64_t x, uint64_t y){
	draw_pixel(x,y);
	return 0;
}


uint64_t sys_clear(){
	cls();
	return 0;
}


uint64_t sys_drawCharPosition(uint64_t l,uint64_t x, uint64_t y){
	draw_char_position(l, x, y);
	return 0;
}

uint64_t sys_getScreenInfo(uint64_t rdi){
	switch(rdi){
		case 0:
			return getScreenWidth();
		case 1:
			return getScreenHeigth();
	}
	return 0;
}

uint64_t sys_setPointer(uint64_t x, uint64_t y) {
	setPointer(x,y);
	return 0;
}

uint64_t sys_ChangeColor(uint64_t blue,uint64_t green,uint64_t red){
	setFontColor(blue,green,red);
	return 0;
}