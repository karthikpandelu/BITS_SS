#include <REGX51.H>
#include<stdio.h>
#include "LCD.h"
#include "i2c.h"
#include "utils.h"
#include<string.h>

static param_t rtc_param;
rtc_t curr_time;
void detect_menu_button_press() {
	if (BTN_MENU == PRESSED) {
		while (BTN_MENU == PRESSED);
		config_RTC();
	}
}

void config_RTC() {
	rtc_param = hh;
	RTC_read_time(&curr_time);
	comwrt(0x0E);	// blink cursor
	while (1) {

		switch (rtc_param) {
		case hh:
			comwrt(0x80);	// hours
			disp_bdc(curr_time.hour);
			break;
		case mm:
			comwrt(0x83);	// min
			disp_bdc(curr_time.min);
			break;
		case ss:
			comwrt(0x86);	// sec
			disp_bdc(curr_time.sec);
			break;
		case DD:
			comwrt(0xC0);	// date
			disp_bdc(curr_time.date);
			break;
		case MM:
			comwrt(0xC3);	// month
			disp_bdc(curr_time.month);
			break;
		case YY:
			comwrt(0xC6);	// year
			disp_bdc(curr_time.year);
			break;
		default:
			comwrt(0x0C); //blink OFF
			RTC_set_time(&curr_time);
			return;

		}
		if (BTN_INC == PRESSED) {
			while (BTN_INC == PRESSED);
			modify_RTC_data(1); //,&curr_time);

		}
		if (BTN_DEC == PRESSED) {
			while (BTN_DEC == PRESSED);
			modify_RTC_data(0); //,&curr_time);

		}
		if (BTN_MENU == PRESSED) {
			while (BTN_MENU == PRESSED);
			rtc_param++;

		}
	}

}

void modify_RTC_data(unsigned char oper) //,rtc_t *curr_time)
{

	switch (rtc_param) {
	case ss:
		vaidate_data(&curr_time.sec, 0, 60, oper);
		break;
	case mm:
		vaidate_data(&curr_time.min, 0, 60, oper);
		break;
	case hh:
		vaidate_data(&curr_time.hour, 0, 24, oper);
		break;
	case DD:
		vaidate_data(&curr_time.date, 1, 31 + 1, oper);  //Max 31
		break;
	case MM:
		vaidate_data(&curr_time.month, 1, 12 + 1, oper); //Max 12
		break;
	case YY:
		vaidate_data(&curr_time.year, 1, 100, oper); // max 99
		break;
	}
}
void vaidate_data(unsigned char *val, unsigned char min, unsigned char max, unsigned char oper) {

	unsigned char dec = BCD_DEC(*val);

	if (oper == 1) {
		dec += 1;
	} else {
		dec -= 1;
	}
	if (dec >= max) {
		dec = min;
	}
	*val = DEC_BCD(dec);

}

unsigned char BCD_DEC(unsigned char bcd) {
	unsigned char dec;

	dec = ((bcd >> 4) * 10) + (bcd & 0x0F);
	return dec;
}
unsigned char DEC_BCD(unsigned char dec) {
	unsigned char bcd;

	bcd = ((dec / 10) << 4) | (dec % 10);
	return bcd;
}
