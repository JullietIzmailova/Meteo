// This module handle Main user screen(Meteo) repaint case ("event") and button-press case ("event")
// Info about which button was pressed  stored in CurBtnIndex

#include "Log.h"
#include "config.h"
#include "DHTSensor.h"
#include "LCDActuator.h"
#include "LEDActuator.h"
#include "LIGHTActuator.h"
#include "BUZZERActuator.h"

void DoShortPress_GUI_METEO()
{
}

void DoLongPress_GUI_METEO()
{
}

void Repaint_GUI_METEO()
{

    LCD_Clear();

    float current_heat_index = DHT_Get_Heat_Index();

    if (current_heat_index > HEAT_INDEX_LEVEL_LOW)
    {
        if (current_heat_index > HEAT_INDEX_LEVEL_HIGH)
        {
            LED_Only_Red_Set_Light();
        }
        else
        {
            LED_Only_Yellow_Set_Light();
        }
    }
    else
    {
        LED_Only_Green_Set_Light();
    }

#ifdef LIGHT_SENSOR_ANALOG_PIN
    float lightValue = LIGHT_GET_data();
    //работаем с Вольтами снятыми с аналогового пина
    LCD_Print_Line4("V => " + String(lightValue) + " Ph => " + String(LIGHT_GET_data()));
#else
    float lightValue = LIGHT_GET_data();
    //работаем с Bool снятого с цифрового пина
    LCD_Print_Line4("A => " + String(lightValue) + " Ph => " + String(LIGHT_GET_data()));
#endif

    LCD_Print_Line1("Temp ====> " + String(DHT_Get_Temperature()) + char(223) + "C");
    LCD_Print_Line2("Hum =====> " + String(DHT_Get_Humidity()) + " %");
    LCD_Print_Line3("curr Hi => " + String(current_heat_index));
};