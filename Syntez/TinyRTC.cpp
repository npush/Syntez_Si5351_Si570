#include "TinyRTC.h"
#include "i2c.h"

#define DS1307_I2C_ADDRESS 0x68

void RTC_Write(RTCData* data)
{
  byte *p=(byte *)data;
  if (i2c_begin_write(DS1307_I2C_ADDRESS)) {
    i2c_write(0);
    for (byte i=7; i > 0; i--) i2c_write(*p++);
    i2c_end();
  }
}

void RTC_Read(void *data, uint8_t start, uint8_t count)
{
  if (i2c_begin_write(DS1307_I2C_ADDRESS)) {
    i2c_write(start);
    i2c_begin_read(DS1307_I2C_ADDRESS);
    i2c_read((uint8_t*)data,count);
    i2c_end();
  }
}

bool RTC_found()
{
  static uint8_t rtc_pooled = false;
  static uint8_t rtc_found = false;
  if (!rtc_pooled) rtc_found = i2c_device_found(DS1307_I2C_ADDRESS);
  return rtc_found;
}

