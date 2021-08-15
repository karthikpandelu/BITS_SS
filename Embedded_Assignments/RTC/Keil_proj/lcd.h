
#ifndef LCD_H
#define LCD_H

#define LCDDATA P1
#define DELAY for(i=0;i<1200;i++)



sbit RS = P2^0; 
sbit RW = P2^1;
sbit EN = P2^2;	

void comwrt(unsigned char);
void datawrt(unsigned char);
void  LCD_initialise();
void display(unsigned char *str);
void disp_bdc(unsigned char bcd);

unsigned char convup(unsigned char bcd);
unsigned char convd(unsigned char bcd);
#endif