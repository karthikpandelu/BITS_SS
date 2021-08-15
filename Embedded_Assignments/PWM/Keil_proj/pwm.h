
#ifndef PWM_H
#define PWM_H

#define PRESSED 0

#define DEFAULT_DUTY_CYCLE	5	//50%
#define MIN_DUTY_CYCLE			1	//10%
#define MAX_DUTY_CYCLE			8	//80%


sbit PWM_OUT =P0^0;
sbit BTN_INC = P0^1;
sbit BTN_DEC = P0^2;




#endif
