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
        String days = String(dt.day);
        if (days.length() < 2)
        {
            days = "0" + days;
        }

        String month = String(dt.month);
        if (month.length() < 2)
        {
            month = "0" + month;
        }


        return days + "." + month + "." + String(dt.year);
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
        String hours = String(dt.hour);
        if (hours.length() < 2)
        {
            hours = "0" + hours;
        }
        String minutes = String(dt.minute);
        if (minutes.length() < 2)
        {
            minutes = "0" + minutes;
        }

        String seconds = String(dt.second);
        if (seconds.length() < 2)
        {
            seconds = "0" + seconds;
        }

        return hours + ":" + minutes + ":" + seconds;
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