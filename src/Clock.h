#include <Arduino.h>
#include "src/libraries/DS3231/DS3231.h"

bool Clock_Setup();
RTCDateTime Get_DateTime();
void Clock_Set_DateTime(String DATE, String TIME);
String Clock_Get_Date();
String Clock_Get_Time();
String Clock_Get_Alarm1();