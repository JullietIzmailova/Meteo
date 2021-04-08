#include <Arduino.h>
#include "src/libraries/DS3231/DS3231.h"

bool Clock_Setup();
RTCDateTime Get_DateTime();
void Clock_Set_DateTime(String DATE, String TIME);
void Clock_Set_DateTime(uint16_t year, uint8_t month, uint8_t day, uint8_t hour, uint8_t minute, uint8_t second );
String Clock_Get_Date();
String Clock_Get_Time();
String Clock_Get_Alarm1();