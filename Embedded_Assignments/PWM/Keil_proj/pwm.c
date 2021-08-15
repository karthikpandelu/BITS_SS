#include <REGX51.H>
#include<stdio.h>
#include<string.h>
#include "pwm.h"

extern unsigned char duty_cycle;

void detect_menu_button_press() {
	if (BTN_INC == PRESSED) {

		duty_cycle++;
		if (duty_cycle > MAX_DUTY_CYCLE)
			duty_cycle = MAX_DUTY_CYCLE;
		while(BTN_INC == PRESSED);		//Debounce

	}
	if (BTN_DEC == PRESSED) {
		duty_cycle--;
		if (duty_cycle < MIN_DUTY_CYCLE)
			duty_cycle = MIN_DUTY_CYCLE;
		while(BTN_DEC == PRESSED);		//Debounce
	}
}

