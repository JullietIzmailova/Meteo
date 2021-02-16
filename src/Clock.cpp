#include "config.h"
#include "Clock.h"
#include "src/libraries/DS3231/DS3231.h"

DS3231 *clock = nullptr;
RTCDateTime dt;

bool Clock_Setup()
{
    clock = new DS3231();
    //CLOCK
    clock->begin();
    // Set sketch compiling time
    clock->setDateTime(__DATE__, __TIME__);
    //TODO: FFR: clock->begin check I2C
    return true;
}

String Clock_Get_Date()
{
    dt = clock->getDateTime();
    return String(dt.day) + "." + String(dt.month) + "." + String(dt.year);
}

String Clock_Get_Time()
{
    dt = clock->getDateTime();
    return String(dt.hour) + ":" + String(dt.minute) + ":" + String(dt.second);
}