#include "config.h"
#include "log.h"
#include "Clock.h"
#include "BUZZERActuator.h"


DS3231 *clock = nullptr;
RTCDateTime dt;

bool buzzerOn = false;

bool Setup_Result = false;

bool Clock_Setup()
{
    clock = new DS3231();
    //CLOCK
    if (clock->begin())
    {
        // Set sketch compiling time
        //clock->setDateTime(__DATE__, __TIME__);
        
        clock->armAlarm1(false);

        clock->clearAlarm1();

        clock->setAlarm1(0, 22, 26, 00, DS3231_MATCH_H_M_S);

        clock->armAlarm1(true);

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

RTCDateTime Get_DateTime()
{
    return clock->getDateTime();
}

void Clock_Set_DateTime(String DATE, String TIME)
{
    clock->setDateTime(DATE.c_str(), TIME.c_str());
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
// retrurn time in format hh:mm:ss
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
        //check alarm

        RTCAlarmTime alarmTime;
        if (clock->isArmed1())
        {
            alarmTime = clock->getAlarm1();
            if ((dt.hour == alarmTime.hour) && (dt.minute == alarmTime.minute))
            {
                Log("alarm");
                BUZZER_Set_sound(buzzerOn);
                buzzerOn = !buzzerOn;
            }
            else
            {
                BUZZER_Set_sound(false);
            }
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