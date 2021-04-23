#include <Arduino.h>
#include "src/libraries/DS3231/DS3231.h"

#define NO_CLOCK "Clock error [0x15]"
#define NO_CLOCK_LED_Color "red"
#define NO_CLOCK_LED_Blink 5
#define NO_CLOCK_Long_Signals 5
#define NO_CLOCK_Short_Signals 5

bool Clock_Setup();
bool Clock_Get_Setup();
RTCDateTime Get_DateTime();
void Clock_Set_DateTime(String DATE, String TIME);
void Clock_Set_DateTime(uint16_t year, uint8_t month, uint8_t day, uint8_t hour, uint8_t minute, uint8_t second );
String Clock_Get_Date();
String Clock_Get_Time();
String Clock_Get_Alarm1();
RTCAlarmTime Clock_Get_Alarm1_RTC();
bool Clock_Get_Alarm1_Status();
void Clock_Set_Alarm1_Status(bool Enable);
void Clock_Set_Alarm1(uint8_t dydw, uint8_t hour, uint8_t minute, uint8_t second, bool armed);
