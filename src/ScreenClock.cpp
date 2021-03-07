#include "main.h"
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
        App_Mode=MODE_SET_CLOCK;
        Log("mode=edit");
    }
}

void Screen_Clock_Draw()
{
    LCDBigNumber_Print_Height2_Right(0, String(Clock_Get_Time()));
    LCD_Print_CenterLine3("__________");                               
    LCD_Print_CenterLine4(String(Clock_Get_Date()));
}
