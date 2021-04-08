#include "config.h"
#include "log.h"
#include "LCDBigNumbers.h"
#include "LEDActuator.h"
#include "LIGHTActuator.h"
#include "BUZZERActuator.h"
#include "Clock.h"
#include "src/libraries/DS3231/DS3231.h"

#include "Buttons.h"
#include "ScreenClock.h"

extern int App_Mode;
extern int App_Saved_Mode;

RTCDateTime editDT;
RTCDateTime saveDT;

#define EDIT_HOURE 0
#define EDIT_MINUTE 1
#define EDIT_SECONDS 2
#define EDIT_DAY 3
#define EDIT_MONTH 4
#define EDIT_YEAR 5

extern int currentEdit;

extern bool blink;

void Screen_Clock_Init()
{
    LCD_Clear();
    Screen_Clock_Draw();
}

void Screen_Clock_Read_Buttons()
{
    if (Get_Button1_LongPress() == true)
    {
        if (App_Mode != MODE_SET_CLOCK)
        {
            App_Mode = MODE_SET_CLOCK;
            currentEdit = EDIT_HOURE;            
            editDT = Get_DateTime();
            saveDT = editDT;
            LCD_Clear();
        }
        else
        {
            App_Mode = MODE_CLOCK;
            if ((saveDT.year != editDT.year) ||
                (saveDT.month != editDT.month) ||
                (saveDT.day != editDT.day) ||
                (saveDT.hour != editDT.hour) ||
                (saveDT.minute != editDT.minute) ||
                (saveDT.second != editDT.second))
            {
                Clock_Set_DateTime(editDT.year, editDT.month, editDT.day, editDT.hour, editDT.minute, editDT.second);
            }
        }
    }

    if ((Get_Button1_ShortPress() == true) && (App_Mode == MODE_SET_CLOCK))
    {
        if (currentEdit >= EDIT_YEAR)
        {
            currentEdit = EDIT_HOURE;
        }
        else
        {
            currentEdit++;
        }
    }

    if ((Get_Button2_ShortPress() == true) && (App_Mode == MODE_SET_CLOCK))
    {
        if (currentEdit == EDIT_YEAR)
        {
            if (editDT.year > 2021)
            {
                editDT.year--;
            }
            else
            {
                editDT.year = 2021;
            }
        }
        else if (currentEdit == EDIT_MONTH)
        {
            if (editDT.month > 1)
            {
                editDT.month--;
            }
            else
            {
                editDT.month = 12;
            }
        }
        else if (currentEdit == EDIT_DAY)
        {
            if (editDT.day > 1)
            {
                editDT.day--;
            }
            else
            {
                editDT.day = 31;
            }
        }
        else if (currentEdit == EDIT_HOURE)
        {
            if (editDT.hour > 0)
            {
                editDT.hour--;
            }
            else
            {
                editDT.hour = 23;
            }
        }
        else if (currentEdit == EDIT_MINUTE)
        {
            if (editDT.minute > 0)
            {
                editDT.minute--;
            }
            else
            {
                editDT.minute = 59;
            }
        }
        else if (currentEdit == EDIT_SECONDS)
        {
            if (editDT.second > 0)
            {
                editDT.second--;
            }
            else
            {
                editDT.second = 59;
            }
        }
    }

    if ((Get_Button3_ShortPress() == true) && (App_Mode == MODE_SET_CLOCK))
    {
        if (currentEdit == EDIT_YEAR)
        {
            editDT.year++;
        }
        else if (currentEdit == EDIT_MONTH)
        {
            if (editDT.month < 12)
            {
                editDT.month++;
            }
            else
            {
                editDT.month = 1;
            }
        }
        else if (currentEdit == EDIT_DAY)
        {
            if (editDT.day < 31)
            {
                editDT.day++;
            }
            else
            {
                editDT.day = 1;
            }
        }
        else if (currentEdit == EDIT_HOURE)
        {
            if (editDT.hour < 23)
            {
                editDT.hour++;
            }
            else
            {
                editDT.hour = 0;
            }
        }
        else if (currentEdit == EDIT_MINUTE)
        {
            if (editDT.minute < 59)
            {
                editDT.minute++;
            }
            else
            {
                editDT.minute = 0;
            }
        }
        else if (currentEdit == EDIT_SECONDS)
        {
            if (editDT.second < 59)
            {
                editDT.second++;
            }
            else
            {
                editDT.second = 0;
            }
        }
    }
}

void Screen_Clock_Draw()
{
    if (App_Mode != MODE_SET_CLOCK)
    {
        LCDBigNumber_Print_Height2_Right(0, String(Clock_Get_Time()));
        LCD_Print_CenterLine3(" ");
        LCD_Print_CenterLine4(String(Clock_Get_Date()));
    }
    else
    {
        LCD_Print_Text(0, 2, "Set date:");
        //Day -----------------------------------
        if ((currentEdit == EDIT_DAY) && (blink))
        {
            LCD_Print_Text(10, 3, "  ");
        }
        else
        {
            LCD_Print_Number(10, 3, 2, editDT.day);
        }
        LCD_Print_Text(12, 3, ".");
        //Month -----------------------------------
        if ((currentEdit == EDIT_MONTH) && (blink))
        {
            LCD_Print_Text(13, 3, "  ");
        }
        else
        {
            LCD_Print_Number(13, 3, 2, editDT.month);
        }
        LCD_Print_Text(15, 3, ".");
        //Year -----------------------------------
        if ((currentEdit == EDIT_YEAR) && (blink))
        {
            LCD_Print_Text(16, 3, "    ");
        }
        else
        {
            LCD_Print_Number(16, 3, 4, editDT.year);
        }
        LCD_Print_Text(0, 0, "Set time:");
        //Houre -----------------------------------
        if ((currentEdit == EDIT_HOURE) && (blink))
        {
            LCD_Print_Text(10, 1, "  ");
        }
        else
        {
            LCD_Print_Number(10, 1, 2, editDT.hour);
        }
        LCD_Print_Text(12, 1, ":");
        //Minute -----------------------------------
        if ((currentEdit == EDIT_MINUTE) && (blink))
        {
            LCD_Print_Text(13, 1, "  ");
        }
        else
        {
            LCD_Print_Number(13, 1, 2, editDT.minute);
        }
        LCD_Print_Text(15, 1, ":");
        //Seconds -----------------------------------
        if ((currentEdit == EDIT_SECONDS) && (blink))
        {
            LCD_Print_Text(16, 1, "  ");
        }
        else
        {
            LCD_Print_Number(16, 1, 2, editDT.second);
        }

        blink = !blink;
    }
}
