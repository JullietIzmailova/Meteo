#include "config.h"
#include "log.h"
#include "Clock.h"
#include "src/libraries/DS3231/DS3231.h"

DS3231 *clock = nullptr;
RTCDateTime dt;

bool Setup_Result = false;

bool Clock_Setup()
{
    clock = new DS3231();
    //CLOCK
    if (clock->begin())
    {
        // Set sketch compiling time
        clock->setDateTime(__DATE__, __TIME__);
        //TODO: FFR: clock->begin check I2C
        dt = clock->getDateTime();
        if (dt.year != 0)
        {
            Log("CLOCK setup complete");
            Setup_Result = true;
            return true;
        }
        else
        {
            Log("CLOCK setup fail");
            return false;
        }
    }
    else
    {
        Log("CLOCK I2C setup fail");
        return false;
    }
}

String Clock_Get_Date()
{

    if (Setup_Result)
    {
        dt = clock->getDateTime();
        return String(dt.day) + "." + String(dt.month) + "." + String(dt.year);
    }
    else
    {
        return "0x0BADFOOD";
    }
}

String Clock_Get_Time()
{
    if (Setup_Result)
    {
        dt = clock->getDateTime();
        return String(dt.hour) + ":" + String(dt.minute) + ":" + String(dt.second);
    }
    else
    {
        return "0x0BADFOOD";
    }
}

String Clock_Get_Alarm1()
{

    if (Setup_Result)
    {
        RTCAlarmTime AlarmTime = clock->getAlarm1();
        return String(AlarmTime.day) + " " + String(AlarmTime.hour) + ":" + String(AlarmTime.minute) + ":" + String(AlarmTime.second);
    }
    else
    {
        return "0x0BADFOOD";
    }
}