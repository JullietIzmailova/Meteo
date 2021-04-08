
#include "config.h"
#include "log.h"
#include "LCDActuator.h"
#include "LEDActuator.h"
#include "LIGHTActuator.h"
#include "BUZZERActuator.h"
#include "Clock.h"

#include "Buttons.h"



#include "ScreenAlarm.h"

extern int App_Mode;
extern int App_Saved_Mode;

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
            Log("To edit");
        }
        else
        {
            //TODO ask user to save changes
            App_Mode = MODE_ALARM;            
            Log("From edit");
        }
        Screen_Alarm_Draw();
    }
    if (App_Mode == MODE_SET_ALARM)
    {
        if (Get_Button2_ShortPress() == true)
        {            
            LCD_Print_Line3("Edit read key 2");
            Screen_Alarm_Draw();
        }

        if (Get_Button3_ShortPress() == true)
        {
            LCD_Print_Line3("Edit read key 3");
            Screen_Alarm_Draw();
        }
    }
}

void Screen_Alarm_Draw()
{
    if (App_Mode != MODE_SET_ALARM)
    {
        LCD_Print_CenterLine1(Clock_Get_Alarm1());
        LCD_Print_CenterLine2(" ");        
        LCD_Print_CenterLine3(" ");
    }
    else
    {
        LCD_Print_CenterLine1(Clock_Get_Alarm1());
        LCD_Print_CenterLine2(" ");        
        LCD_Print_CenterLine3("Time Edit Mode");
    }
}
