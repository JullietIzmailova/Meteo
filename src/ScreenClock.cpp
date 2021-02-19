#include "config.h"
#include "log.h"
#include "LCDBigNumbers.h"
#include "LEDActuator.h"
#include "LIGHTActuator.h"
#include "BUZZERActuator.h"
#include "Clock.h"

#include "Buttons.h"

#include "Menu.h"

#include "ScreenClock.h"

void Screen_Clock_Init()
{
    LCD_Clear();
    Screen_Clock_Draw();
}

void Screen_Clock_Read_Buttons()
{
    if (Get_Button1_LongPress() == true)
    {
        if (!Get_Edit_Mode())
        {
            Set_Edit_Mode(true);
            Log("To edit");
        }
        else
        {
            //TODO ask user to save changes
            Set_Edit_Mode(false);
            Log("From edit");
        }
        Screen_Clock_Draw();
    }
    if (Get_Edit_Mode())
    {
        if (Get_Button2_ShortPress() == true)
        {
            LCD_Print_Line3("Edit read key 2");
            Screen_Clock_Draw();
        }

        if (Get_Button3_ShortPress() == true)
        {
            LCD_Print_Line3("Edit read key 3");
            Screen_Clock_Draw();
        }
    }
}

void Screen_Clock_Draw()
{
    if (!Get_Edit_Mode())
    {
        LCDBigNumber_Print_Height2_Right(0, String(Clock_Get_Date()));
        LCDBigNumber_Print_Height2_Right(2, String(Clock_Get_Time()));
        LCD_Print_CenterLine3(" ");
    }
    else
    {
        LCD_Print_CenterLine1(Clock_Get_Date());
        LCD_Print_CenterLine2(Clock_Get_Time());
        LCD_Print_CenterLine3("Time Edit Mode");
    }
}
