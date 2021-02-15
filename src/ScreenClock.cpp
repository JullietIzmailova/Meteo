#include "config.h"
#include "log.h"
#include "LCDActuator.h"
#include "LEDActuator.h"
#include "LIGHTActuator.h"
#include "BUZZERActuator.h"
#include "Clock.h"

#include "Buttons.h"
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
        Log("Go to MENU");
        Set_Current_Screen(MODE_MENU);
    }
}

void Screen_Clock_Draw()
{
    LCD_Clear();
    LCD_Print_Line1(Clock_Get_Date());
    LCD_Print_Line2(Clock_Get_Time());
}
