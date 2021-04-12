/* ----------------------------------------------------------------------------
Ready IoT Solution - OWLOS Meteo
Copyright 2020, 2021 by:
- Julliet Izmailova
- Vitalii Glushchenko (cehoweek@gmail.com)
- Denys Melnychuk (meldenvar@gmail.com)
- Denis Kirin (deniskirinacs@gmail.com)
- Serhii Lehkii (sergey@light.kiev.ua)

This file is part of Ready IoT Solution - OWLOS

OWLOS is free software : you can redistribute it and/or modify it under the
terms of the GNU General Public License as published by the Free Software
Foundation, either version 3 of the License, or (at your option) any later
version.

OWLOS is distributed in the hope that it will be useful, but WITHOUT ANY
WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS
FOR A PARTICULAR PURPOSE.
See the GNU General Public License for more details.

You should have received a copy of the GNU General Public License along
with OWLOS. If not, see < https://www.gnu.org/licenses/>.

GitHub: https://github.com/KirinDenis/Meteo

(Этот файл — часть Ready IoT Solution - OWLOS.

OWLOS - свободная программа: вы можете перераспространять ее и/или изменять
ее на условиях Стандартной общественной лицензии GNU в том виде, в каком она
была опубликована Фондом свободного программного обеспечения; версии 3
лицензии, любой более поздней версии.

OWLOS распространяется в надежде, что она будет полезной, но БЕЗО ВСЯКИХ
ГАРАНТИЙ; даже без неявной гарантии ТОВАРНОГО ВИДА или ПРИГОДНОСТИ ДЛЯ
ОПРЕДЕЛЕННЫХ ЦЕЛЕЙ.
Подробнее см.в Стандартной общественной лицензии GNU.

Вы должны были получить копию Стандартной общественной лицензии GNU вместе с
этой программой. Если это не так, см. <https://www.gnu.org/licenses/>.)
--------------------------------------------------------------------------------------*/

#include "config.h"
#include "log.h"
#include "Clock.h"
#include "BUZZERActuator.h"

DS3231 *clock = nullptr;
RTCDateTime dt;

extern bool AnyKey;
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

        //  clock->armAlarm1(false);

        //        clock->clearAlarm1();

        //        clock->setAlarm1(0, 22, 26, 00, DS3231_MATCH_H_M_S);

        //        clock->armAlarm1(true);

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

bool Clock_Get_Setup()
{
    return Setup_Result;
}


RTCDateTime Get_DateTime()
{
    return clock->getDateTime();
}

void Clock_Set_DateTime(String DATE, String TIME)
{
    clock->setDateTime(DATE.c_str(), TIME.c_str());
}

void Clock_Set_DateTime(uint16_t year, uint8_t month, uint8_t day, uint8_t hour, uint8_t minute, uint8_t second)
{
    clock->setDateTime(year, month, day, hour, minute, second);
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
        return NO_CLOCK;
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
                if (!AnyKey)
                {
                    BUZZER_Set_sound(buzzerOn);
                    buzzerOn = !buzzerOn;
                }
                else
                {
                    BUZZER_Set_sound(false);
                }
            }
            else
            {
                BUZZER_Set_sound(false);
                AnyKey = false;
            }
        }

        return hours + ":" + minutes + ":" + seconds;
    }
    else
    {
        return NO_CLOCK;
    }
}

RTCAlarmTime Clock_Get_Alarm1_RTC()
{
    if (Setup_Result)
    {
        return clock->getAlarm1();
    }
    RTCAlarmTime AlarmTime;
    return AlarmTime;
}

String Clock_Get_Alarm1()
{
    if (Setup_Result)
    {
        RTCAlarmTime AlarmTime = Clock_Get_Alarm1_RTC();

        String hours = String(AlarmTime.hour);
        if (hours.length() < 2)
        {
            hours = "0" + hours;
        }
        String minutes = String(AlarmTime.minute);
        if (minutes.length() < 2)
        {
            minutes = "0" + minutes;
        }

        String seconds = String(AlarmTime.second);
        if (seconds.length() < 2)
        {
            seconds = "0" + seconds;
        }

        return hours + ":" + minutes + ":" + seconds;
    }
    else
    {
        return NO_CLOCK;
    }
}

bool Clock_Get_Alarm1_Status()
{
    if (Setup_Result)
    {
        return clock->isArmed1();
    }
    return false;
}

void Clock_Set_Alarm1_Status(bool Enable)
{
    if (Setup_Result)
    {
        clock->armAlarm1(Enable);
    }
}

void Clock_Set_Alarm1(uint8_t dydw, uint8_t hour, uint8_t minute, uint8_t second, bool armed)
{
    clock->setAlarm1(dydw, hour, minute, second, DS3231_MATCH_H_M_S, armed);
}