
#ifndef UTILS_H
#define UTILS_H

#define PRESSED 0

sbit BTN_MENU =P0^0;
sbit BTN_INC = P0^1;
sbit BTN_DEC = P0^2;

typedef enum {hh,mm,ss,DD,MM,YY}param_t;


void detect_menu_button_press();
void config_RTC();
void modify_RTC_data(unsigned char oper);
void vaidate_data(unsigned char *val,unsigned char min,unsigned char max ,unsigned char oper);
unsigned char DEC_BCD(unsigned char dec);
unsigned char BCD_DEC(unsigned char bcd);



#endif
