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
#include "LCDActuator.h"
#include "LCDBigNumbers.h"
#include "LEDActuator.h"
#include "LIGHTActuator.h"
#include "BUZZERActuator.h"
#include "Clock.h"

#include "Buttons.h"

#include "ScreenAlarm.h"

extern int App_Mode;
extern int App_Saved_Mode;

#define ALARM_HOURE 0
#define ALARM_MINUTE 1
#define ALARM_SECONDS 2
#define ALARM_ONOFF 3

RTCAlarmTime editRTC;
bool editAlarmOnOff;

extern int currentEdit;
extern bool blink;

void Screen_Alarm_Init()
{
    LCD_Clear();
    Screen_Alarm_Draw();
}

void Screen_Alarm_Read_Buttons()
{
    if (Get_Button1_LongPress() == true)
    {
        if (App_Mode != MODE_SET_ALARM)
        {
            App_Mode = MODE_SET_ALARM;
            currentEdit = ALARM_HOURE;
            editRTC = Clock_Get_Alarm1_RTC();
            editAlarmOnOff = Clock_Get_Alarm1_Status();
            LCD_Clear();
        }
        else
        {
            App_Mode = MODE_ALARM;
            Clock_Set_Alarm1(editRTC.day, editRTC.hour, editRTC.minute, editRTC.second, editAlarmOnOff);
        }
        Screen_Alarm_Draw();
    }

    if ((Get_Button1_ShortPress() == true) && (App_Mode == MODE_SET_ALARM))
    {
        if (currentEdit >= ALARM_ONOFF)
        {
            currentEdit = ALARM_HOURE;
        }
        else
        {
            currentEdit++;
        }
    }

    if (App_Mode == MODE_SET_ALARM)
    {
        if (Get_Button2_ShortPress() == true)
        {
            if (currentEdit == ALARM_HOURE)
            {
                if (editRTC.hour > 0)
                {
                    editRTC.hour--;
                }
                else
                {
                    editRTC.hour = 23;
                }
            }
            else if (currentEdit == ALARM_MINUTE)
            {
                if (editRTC.minute > 0)
                {
                    editRTC.minute--;
                }
                else
                {
                    editRTC.minute = 59;
                }
            }
            else if (currentEdit == ALARM_SECONDS)
            {
                if (editRTC.second > 0)
                {
                    editRTC.second--;
                }
                else
                {
                    editRTC.second = 59;
                }
            }
            else if (currentEdit == ALARM_ONOFF)
            {
                editAlarmOnOff = !editAlarmOnOff;
            }
        }

        if (Get_Button3_ShortPress() == true)
        {
            if (currentEdit == ALARM_HOURE)
            {
                if (editRTC.hour < 23)
                {
                    editRTC.hour++;
                }
                else
                {
                    editRTC.hour = 0;
                }
            }
            else if (currentEdit == ALARM_MINUTE)
            {
                if (editRTC.minute < 59)
                {
                    editRTC.minute++;
                }
                else
                {
                    editRTC.minute = 0;
                }
            }
            else if (currentEdit == ALARM_SECONDS)
            {
                if (editRTC.second < 59)
                {
                    editRTC.second++;
                }
                else
                {
                    editRTC.second = 0;
                }
            }
            else if (currentEdit == ALARM_ONOFF)
            {
                editAlarmOnOff = !editAlarmOnOff;
            }
        }
    }
}

void Screen_Alarm_Draw()
{
    if (App_Mode != MODE_SET_ALARM)
    {
        LCD_Print_CenterLine1("Alarm at:");
        LCDBigNumber_Print_Height2_Left(1, Clock_Get_Alarm1());
        if (Clock_Get_Alarm1_Status())
        {
            LCD_Print_CenterLine4("[on]");
        }
        else
        {
            LCD_Print_CenterLine4("[off]");
        }
    }
    else
    {
        LCD_Print_Text(0, 0, "Set alarm:");
        //Houre -----------------------------------
        if ((currentEdit == ALARM_HOURE) && (blink))
        {
            LCD_Print_Text(10, 1, "  ");
        }
        else
        {
            LCD_Print_Number(10, 1, 2, editRTC.hour);
        }
        LCD_Print_Text(12, 1, ":");
        //Minute -----------------------------------
        if ((currentEdit == ALARM_MINUTE) && (blink))
        {
            LCD_Print_Text(13, 1, "  ");
        }
        else
        {
            LCD_Print_Number(13, 1, 2, editRTC.minute);
        }
        LCD_Print_Text(15, 1, ":");
        //Seconds -----------------------------------
        if ((currentEdit == ALARM_SECONDS) && (blink))
        {
            LCD_Print_Text(16, 1, "  ");
        }
        else
        {
            LCD_Print_Number(16, 1, 2, editRTC.second);
        }
        //OnOff -----------------------------------
        if ((currentEdit == ALARM_ONOFF) && (blink))
        {
            LCD_Print_CenterLine4("    ");
        }
        else
        {
            if (editAlarmOnOff)
            {
                LCD_Print_CenterLine4("[on]");
            }
            else
            {
                LCD_Print_CenterLine4("[off]");
            }
        }
        blink = !blink;
    }
}
