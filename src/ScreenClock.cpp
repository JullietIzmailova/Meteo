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

#define EDIT_HOURE 3
#define EDIT_MINUTE 4
#define EDIT_SECONDS 5
int currentEdit = EDIT_HOURE;

bool blink = false;

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
            editDT = Get_DateTime();
            Log("mode=edit");
        }
        else
        {
            App_Mode = MODE_CLOCK;
            Log("mode=view");
        }
    }

    if ((Get_Button1_ShortPress() == true) && (App_Mode == MODE_SET_CLOCK))
    {
        if (currentEdit >= EDIT_SECONDS)
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
         if (currentEdit == EDIT_HOURE)
         {
             if (editDT.hour > 0)
             {
                 editDT.hour--;
             }
             else 
             {
                 editDT.hour = 24;
             }
         }
    }

    if ((Get_Button3_ShortPress() == true) && (App_Mode == MODE_SET_CLOCK))
    {
         if (currentEdit == EDIT_HOURE)
         {
             if (editDT.hour < 24)
             {
                 editDT.hour++;
             }
             else 
             {
                 editDT.hour = 0;
             }
         }
    }

}

void Screen_Clock_Draw()
{
    if (App_Mode != MODE_SET_CLOCK)
    {
        LCDBigNumber_Print_Height2_Right(0, String(Clock_Get_Time()));
        LCD_Print_CenterLine3("__________");
        LCD_Print_CenterLine4(String(Clock_Get_Date()));
    }
    else
    {
        if ((currentEdit == EDIT_HOURE) && (blink))
        {
            LCD_Print_Text(0, 0, "  ");
        }
        else
        {
            LCD_Print_Number(0, 0, 2, editDT.hour);
        }
        LCD_Print_Text(2, 0, ":");

        if ((currentEdit == EDIT_MINUTE) && (blink))
        {
            LCD_Print_Text(3, 0, "  ");
        }
        else
        {
            LCD_Print_Number(3, 0, 2, editDT.minute);
        }
        LCD_Print_Text(5, 0, ":");

        if ((currentEdit == EDIT_SECONDS) && (blink))
        {
            LCD_Print_Text(6, 0, "  ");
        }
        else
        {
            LCD_Print_Number(6, 0, 2, editDT.second);
        }

        blink = !blink;
    }
}
