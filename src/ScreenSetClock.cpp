#include "Buttons.h"
#include "main.h"
#include "config.h"
#include "log.h"
#include "LCDBigNumbers.h"
#include "LEDActuator.h"
#include "LIGHTActuator.h"
#include "BUZZERActuator.h"
#include "Clock.h"
#include "ScreenSetClock.h"

void Screen_SetClock_Init()
{
    LCD_Clear();
    Screen_SetClock_Draw();
}

void Screen_SetClock_Read_Buttons()
{
    if (Get_Button1_LongPress() == true)
    {
        App_Mode=App_Saved_Mode;
        Log("To edit");
    }
}

void Screen_SetClock_Draw()
{

}