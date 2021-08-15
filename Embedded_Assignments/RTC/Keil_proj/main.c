#include <REGX51.H>
#include<stdio.h>
#include "LCD.h"
#include "i2c.h"
#include "utils.h"
#include<string.h>

void delay_50ms(unsigned char duration);
rtc_t rtc_time;

void main() {
	LCD_initialise();

	while (1) {
		RTC_read_time(&rtc_time);

		comwrt(0x80);
		disp_bdc(rtc_time.hour);
		datawrt(':');
		disp_bdc(rtc_time.min);
		datawrt(':');
		disp_bdc(rtc_time.sec);
		datawrt(' ');
		comwrt(0xC0);

		disp_bdc(rtc_time.date);
		datawrt('/');
		disp_bdc(rtc_time.month);
		datawrt('/');
		disp_bdc(rtc_time.year);

		detect_menu_button_press(); // settings menu 

		delay_50ms(20);	// 1sec delay
	}
}

void delay_50ms(unsigned char duration) {
	unsigned char i;
	for (i = 0; i < duration; i++) {
		TH0 = 0X4B;
		TL0 = 0XFD;
		TF0 = 0;
		TR0 = 1;
		while (TF0 == 0);
	}
}

