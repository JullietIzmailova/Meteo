#include "main.h"
#include "config.h"
#include "log.h"
#include "DHTSensor.h"
#include "LCDBigNumbers.h"
#include "LEDActuator.h"
#include "LIGHTActuator.h"
#include "BUZZERActuator.h"

#include "Clock.h"
#include "Buttons.h"

#include "Menu.h"

#include "ScreenMeteo.h"

int leftPosition = 0;

extern int App_Mode;
extern int App_Saved_Mode;


void Screen_Meteo_Init()
{
    LCD_Clear();
    Screen_Meteo_Draw();
}

void Screen_Meteo_Read_Buttons()
{
    if (Get_Button1_LongPress() == true)
    {
        if (!Is_Edit_Mode())
        {
            App_Mode = MODE_METEO;
            
            Log("To edit");
        }
        else
        {
            //TODO ask user to save changes
            App_Mode = MODE_METEO;
            Log("From edit");
        }
        Screen_Meteo_Draw();
    }
    if (Is_Edit_Mode())
    {
        if (Get_Button2_ShortPress() == true)
        {
            LCD_Print_Line3("Edit read key 2");
            Screen_Meteo_Draw();
        }

        if (Get_Button3_ShortPress() == true)
        {
            LCD_Print_Line3("Edit read key 3");
            Screen_Meteo_Draw();
        }
    }
}

void Screen_Meteo_Draw()
{

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
    //float lightValue = LIGHT_GET_data();
    //работаем с Вольтами снятыми с аналогового пина
    //LCD_Print_Line4("V => " + String(lightValue) + " Ph => " + String(LIGHT_GET_data()));
#else
    float lightValue = LIGHT_GET_data();
    //работаем с Bool снятого с цифрового пина
    LCD_Print_Line4("A => " + String(lightValue) + " Ph => " + String(LIGHT_GET_data()));
#endif

    leftPosition++;

    String str_temp = String((int)DHT_Get_Temperature())+ char(223) + "C";
    String str_hum = String((int)DHT_Get_Humidity())+"%";

    String outString = Clock_Get_Date() + " " + str_temp + " " + str_hum;
    //20

    LCDBigNumber_Print_Height2_Right(0, String(Clock_Get_Time()));
    LCD_Print_CenterLine3(Clock_Get_Date() + " " + str_temp + " " + str_hum);                               
    LCD_Print_CenterLine4("heat " + String((int)DHT_Get_Heat_Index()) +" light " + String(LIGHT_GET_data()));


//    Log(str_temp);
//    Log(str_hum);

    //LCDBigNumber_Print_Height2_Right(0, str_temp);
    //LCDBigNumber_Print_Height2_Right(2, str_hum);

    // LCD_Print_Line1("Temp ====> " + String(DHT_Get_Temperature()) + char(223) + "C");
    // LCD_Print_Line2("Hum =====> " + String(DHT_Get_Humidity()) + " %");
    // LCD_Print_Line3("curr Hi => " + String(current_heat_index));
}
