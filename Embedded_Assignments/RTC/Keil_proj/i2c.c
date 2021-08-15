#include <REGX51.H>
#include<stdio.h>
#include "i2c.h"
#include<string.h>

unsigned char bdata RTC_DATA;

sbit lsb = RTC_DATA ^ 0;
sbit msb = RTC_DATA ^ 7;

void RTC_read_time(rtc_t *rtc_time) {
	i2c_start();
	i2c_send(DS1307_WRITE_ADDR);
	i2c_send(0x00);
	i2c_stop();
	i2c_start();
	i2c_send(DS1307_READ_ADDR);

	rtc_time->sec = i2c_read(1);
	rtc_time->min = i2c_read(1);
	rtc_time->hour = i2c_read(1);
	rtc_time->weekDay = i2c_read(1);
	rtc_time->date = i2c_read(1);
	rtc_time->month = i2c_read(1);
	rtc_time->year = i2c_read(0);

	i2c_stop();

}

void RTC_set_time(rtc_t *rtc_time) {
	i2c_start();
	
	i2c_send(DS1307_WRITE_ADDR);
	i2c_send(0x00);
	
	i2c_send(rtc_time->sec);
	i2c_send(rtc_time->min);
	i2c_send(rtc_time->hour);
	i2c_send(rtc_time->weekDay);
	i2c_send(rtc_time->date);
	i2c_send(rtc_time->month);
	i2c_send(rtc_time->year);

	i2c_stop();

}
void i2c_start(void) {
	SDA = 1;
	SCL = 1;
	SDA = 0;
	SCL = 0;
}

void i2c_send(unsigned char send) {
	unsigned char i;
	RTC_DATA = send;
	for (i = 0; i <= 7; i++) {
		SDA = msb;
		SCL = 1;
		SCL = 0;
		RTC_DATA = RTC_DATA << 1;
	}
	while (SDA != 0);
	SCL = 1;
	SCL = 0;
}

unsigned char i2c_read(unsigned char ack) {
	unsigned char i;
	lsb = SDA;
	for (i = 0; i <= 7; i++) {
		RTC_DATA = RTC_DATA << 1;
		lsb = SDA;
		SCL = 1;
		SCL = 0;
	}

	if (ack == 1)
		i2c_Ack();
	else
		i2c_NoAck();
	return (RTC_DATA);
}

void i2c_stop(void) {
	SDA = 0;
	SCL = 1;
	SDA = 1;
	SCL = 0;
}
void i2c_Ack(void) {
	SDA = 0;        //Pull SDA low to indicate Positive ACK
	SCL = 1;
	SCL = 0;
	SDA = 1;        // Pull SDA back to High(IDLE state)
}
void i2c_NoAck(void) {
	SDA = 1;         //Pull SDA high to indicate Negative/NO ACK
	SCL = 1;
	SCL = 0;
	SCL = 1;         // Set SCL 
}
