#include <REGX51.H>
#include<stdio.h>
#include "LCD.h"
#include<string.h>

#define LCDDATA P1
#define DELAY for(i=0;i<1200;i++)

void LCD_initialise() {

	unsigned int i, j;

	int com[5] = { 0x38, 0x0C, 0x01, 0x06, 0x80 };
	for (j = 0; j <= 4; j++) {
		comwrt(com[j]);
		DELAY;
	}

}

void comwrt(unsigned char dat) {
	unsigned int i;
	LCDDATA = dat;
	RS = 0;
	RW = 0;
	EN = 1;
	DELAY;
	EN = 0;
}

void datawrt(unsigned char dat) {
	unsigned int i;
	LCDDATA = dat;
	RS = 1;
	RW = 0;
	EN = 1;
	DELAY;
	EN = 0;
}

void display(unsigned char *str) {
	int i;
	for (; *str != 0; str++) {
		datawrt(*str);
		DELAY;

	}
}

void disp_bdc(unsigned char bcd) {
	datawrt(convup(bcd));
	datawrt(convd(bcd));
}
unsigned char convup(unsigned char bcd) {
	return ((bcd >> 4) + 48);
}
unsigned char convd(unsigned char bcd) {
	return ((bcd & 0x0F) + 48);
}

