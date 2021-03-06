#include "Buttons.h"


void Screen_SetClock_Init()
{
    LCD_Clear();
    Screen_SetClock_Draw();
}

void Screen_SetClock_Read_Buttons()
{
    if (Get_Button1_LongPress() == true)
    {
        Set_Clock_Mode(true);
        Log("To edit");
    }
}

void Screen_SetClock_Draw()
{

}