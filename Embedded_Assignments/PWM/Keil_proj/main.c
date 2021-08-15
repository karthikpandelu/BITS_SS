#include <REGX51.H>
#include<stdio.h>
#include<string.h>
#include "pwm.h"

void delay_1ms(unsigned char duration);
void init_timer();
unsigned char duty_cycle=DEFAULT_DUTY_CYCLE;

void main() {
	
	init_timer();
	
	while (1) {
		
		detect_menu_button_press();
		
	}
}
void init_timer()
{
	TMOD=0x11;	//Timer 0 & Timer 1 in 16 bit timer mode
	
	/*Timer 0 as 10ms timer with timer_interrupt*/
	/* TH0 & TL0 calculation =[0xFFFF-(10ms/1.085us)]*/
		TH0 = 0XDB;
		TL0 = 0XFF;
		TF0 = 0;
		TR0 = 1;
		ET0=1;	// Timer 0 interrupt_enable
		EA=1;		// global interrupt_enable
	
}

void Timer0_ISR() interrupt 1	/* Timer0 ISR */
{

	
	PWM_OUT= 1;  		/* Toggle port pin */
	TH0 = 0xDB;      	/* 10ms timer value */
	TL0 = 0xFF;      	
	TF0=0;	//clear flag
	delay_1ms(duty_cycle);
	PWM_OUT= 0;  		/* Toggle port pin */

}

void delay_1ms(unsigned char duration) {
	unsigned char i;
	for (i = 0; i < duration; i++) {
		TH1 = 0XFC;
		TL1 = 0X67;
		TF1 = 0;
		TR1 = 1;
		while (TF1 == 0);
	}
}

