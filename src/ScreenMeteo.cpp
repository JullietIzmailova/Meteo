/* ----------------------------------------------------------------------------
Ready IoT Solution - OWLOS Meteo
Copyright 2020, 2021 by:
- Julliet Izmailova
- Vitalii Glushchenko (cehoweek@gmail.com)
- Denys Melnychuk (meldenvar@gmail.com)
- Denis Kirin (deniskirinacs@gmail.com)
- Serhii Lehkii (sergey@light.kiev.ua)

This file is part of Ready IoT Solution - OWLOS

OWLOS is free software : you can redistribute it and/or modify it under the
terms of the GNU General Public License as published by the Free Software
Foundation, either version 3 of the License, or (at your option) any later
version.

OWLOS is distributed in the hope that it will be useful, but WITHOUT ANY
WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS
FOR A PARTICULAR PURPOSE.
See the GNU General Public License for more details.

You should have received a copy of the GNU General Public License along
with OWLOS. If not, see < https://www.gnu.org/licenses/>.

GitHub: https://github.com/KirinDenis/Meteo

(Этот файл — часть Ready IoT Solution - OWLOS.

OWLOS - свободная программа: вы можете перераспространять ее и/или изменять
ее на условиях Стандартной общественной лицензии GNU в том виде, в каком она
была опубликована Фондом свободного программного обеспечения; версии 3
лицензии, любой более поздней версии.

OWLOS распространяется в надежде, что она будет полезной, но БЕЗО ВСЯКИХ
ГАРАНТИЙ; даже без неявной гарантии ТОВАРНОГО ВИДА или ПРИГОДНОСТИ ДЛЯ
ОПРЕДЕЛЕННЫХ ЦЕЛЕЙ.
Подробнее см.в Стандартной общественной лицензии GNU.

Вы должны были получить копию Стандартной общественной лицензии GNU вместе с
этой программой. Если это не так, см. <https://www.gnu.org/licenses/>.)
--------------------------------------------------------------------------------------*/

#include "config.h"
#include "log.h"
#include "DHTSensor.h"
#include "LCDBigNumbers.h"
#include "LEDActuator.h"
#include "LIGHTActuator.h"
#include "BUZZERActuator.h"

#include "Clock.h"
#include "Buttons.h"

#include "ScreenMeteo.h"

int leftPosition = 0;

extern int App_Mode;
extern int App_Saved_Mode;

bool hoursEdit = true;

void Screen_Meteo_Init()
{
    LCD_Clear();
    Screen_Meteo_Draw();
}

void Screen_Meteo_Read_Buttons()
{
    //FFR: Meteo modes
    /*
    if (Get_Button1_LongPress() == true)
    {
        if (App_Mode != MODE_SET_METEO)
        {
            App_Mode = MODE_SET_METEO;
            hoursEdit = true;    
        }
        else
        {
            //TODO ask user to save changes
            App_Mode = MODE_METEO;            
        }
        Screen_Meteo_Draw();
    }

    if (App_Mode == MODE_SET_METEO)
    {
        if (Get_Button2_ShortPress() == true)
        {    
        }

        if (Get_Button3_ShortPress() == true)
        {
        }
    }
    */
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
    //LCD_Print_Line4("A => " + String(lightValue) + " Ph => " + String(LIGHT_GET_data()));
#endif

    //Temperature
    LCDBigNumber_Print_Height2_Left(0, String((int)DHT_Get_Temperature()));
    LCD_Print_Text(6, 0, String(char(223)));
    LCD_Print_Text(6, 1, "C");

    //Heat index
    String heatStr = " H:" + String((int)DHT_Get_Heat_Index());
    for (int i = 0; i < 7 - heatStr.length(); i++)
    {
        heatStr += " ";
    }
    LCD_Print_Text(7, 0, heatStr);
    //Light
    String lightStr = " L:" + String((int)LIGHT_GET_data());
    for (int i = 0; i < 7 - lightStr.length(); i++)
    {
        lightStr += " ";
    }
    LCD_Print_Text(7, 1, lightStr);

    //Humidity
    LCDBigNumber_Print_Height2_Offset(0, 20 - 7, String((int)DHT_Get_Humidity()));
    LCD_Print_Text(19, 1, "%");

    //Date Time
    LCD_Print_CenterLine3(" ");
    
    if(Clock_Get_Setup())
    {
    LCD_Print_CenterLine4(Clock_Get_Date() + " " + Clock_Get_Time());
    }
    else{
        LCD_Print_CenterLine4(NO_CLOCK);
    }

}
