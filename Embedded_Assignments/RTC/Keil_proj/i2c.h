
#ifndef I2C_H
#define I2C_H

#define DS1307_WRITE_ADDR 0xD0
#define DS1307_READ_ADDR 0xD1

sbit SDA = 	P3^7;
sbit SCL = 	P3^6;

typedef struct
{
  unsigned char sec;
  unsigned char min;
  unsigned char hour;
  unsigned char weekDay;
  unsigned char date;
  unsigned char month;
  unsigned char year;  
}rtc_t;

void RTC_Init(void);
void RTC_read_time(rtc_t *rtc_time);
void RTC_set_time(rtc_t *rtc_time);
unsigned char i2c_read_addr(unsigned char addr, unsigned char ack);
void i2c_start(void);
void i2c_send (unsigned char);
unsigned char i2c_read(unsigned char ack);
void i2c_stop(void);
void i2c_Ack(void);
void i2c_NoAck(void);



#endif