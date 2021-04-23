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
#include "SetupSignals.h"


int temperature_Save = ABSOLUTE_ZERO;
int humidity_Save = 101;
int light_Save = -1;
int heat_index_Save = -1;
String date_Save = "";
String time_Save = "";

//Вызывается когда экран переключен в режимы MODE_METEO или MODE_SET_METEO
void Screen_Meteo_Init()
{
    temperature_Save = ABSOLUTE_ZERO + -1;
    humidity_Save = 101; //%
    light_Save = -1;
    heat_index_Save = -1;
    date_Save = "";
    time_Save = "";

    LCD_Clear();
    Screen_Meteo_Draw();
}

//Для режимов экрана: MODE_METEO и MODE_SET_METEO
//Главная процедура loop() вызывает эту процедуру каждый раз когда этот экран активен.
//Таким образом кнопки нажатые пользователем для этого экрана будуту обработаны этой
//процедурой. Подобные процедуры для других режимов экрана - вызваны не будут.
void Screen_Meteo_Read_Buttons()
{
    //FFR TODO: Meteo modes
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

//Для режимов экрана: MODE_METEO и MODE_SET_METEO
//Главная процедура loop() вызывает эту процедуру через определенный интервал и каждый раз когда этот
//экран активен. Все данные относящиеся к данному режиму экрана должны быть выведены этой процедурой.
void Screen_Meteo_Draw()
{

    
    if (DHT_Get_Status())
    {
        unsigned int length;
        //Получаем Heat Index и в зависемости от его значения зажигаем зеленый, желтый или красный светодиоды
        //Подробнее смотрите config.h HEAT_INDEX_LEVEL_NNN
        int current_heat_index = (int)DHT_Get_Heat_Index();

        if (current_heat_index != heat_index_Save)
        {

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
        }

        int current_Temperature = (int)DHT_Get_Temperature();
        if (current_Temperature != temperature_Save)
        {
            //Выводим текущее значение температуры полученное от DHT сенсора
            //Используем (int) что бы убрать float часть, она не нужна пользователю (пример 25.44 переводим в 25)
            LCDBigNumber_Print_Height2_Left(0, String(current_Temperature));
            LCD_Print_Text(6, 0, String(char(223)));
            LCD_Print_Text(6, 1, "C");
            temperature_Save = current_Temperature;
        }

        if (current_heat_index != heat_index_Save)
        {
            //Выводим значение Heat Index на экран (оно так же дублируется светодиодами)
            //На экране нам необходимо "забить" пробелами оставшиеся символы, что бы избежать "мусора" на экране
            //от предидущих прорисовок
            String heatStr = " H:" + String(current_heat_index);
            length = 6 - heatStr.length();
            for (unsigned int i = 0; i < length; i++)
            {
                heatStr += " ";
            }
            LCD_Print_Text(7, 0, heatStr);
            heat_index_Save = current_heat_index;
        }

        int current_Humidity = (int)DHT_Get_Humidity();
        if (current_Humidity != humidity_Save)
        {
            //Выводим значение влажности
            LCDBigNumber_Print_Height2_Offset(0, 20 - 7, String(current_Humidity));
            LCD_Print_Text(19, 1, "%");
            LCD_Print_CenterLine3(" ");
            humidity_Save = current_Humidity;
        }
    }
    else
    {      
      
            //Если датчик темпетаруты не работает 
            
            //1. Выводим значение влажности = 99
            LCDBigNumber_Print_Height2_Offset(0, 20 - 7, String("......"));
            LCD_Print_Text(19, 1, "%");
            humidity_Save = 0;
            
            //2.Выводим значение Heat Index на экран
            String heatStr = " H:" + String(00);
            unsigned int currentLength = 6 - heatStr.length();
            for (unsigned int i = 0; i < currentLength; i++)
            {
                heatStr += " ";
            }
            LCD_Print_Text(7, 0, heatStr);
            heat_index_Save = 0;

             //3. Выводим значение температуры = 99
            LCDBigNumber_Print_Height2_Left(0, String("......"));
            LCD_Print_Text(6, 0, String(char(223)));
            LCD_Print_Text(6, 1, "C");
            temperature_Save = 0;

            LCD_Print_CenterLine3(NO_DHT);
            Setup_Signals_Blinking_Light(NO_DHT_LED_Blink, NO_DHT_LED_Color);
    }

    int current_Light = (int)LIGHT_GET_data();
    if (current_Light != light_Save)
    {
        //Показание сенсора освещенности, так же как Heat Index с удалением "мусора"
        String lightStr = " L:" + String((int)LIGHT_GET_data());
        unsigned int length = 6 - lightStr.length();
        for (unsigned int i = 0; i < length; i++)
        {
            lightStr += " ";
        }
        LCD_Print_Text(7, 1, lightStr);
        light_Save = current_Light;
    }

    if (Clock_Get_Setup())
    {
        //Выводим текущею дату и время
        String current_Date = Clock_Get_Date();
        if (!current_Date.equals(date_Save))
        {
            LCD_Print_Text(0, 3, current_Date);
            date_Save = current_Date;
        }

        String current_Time = Clock_Get_Time();
        if (!current_Time.equals(time_Save))
        {
            LCD_Print_Text(20 - current_Time.length(), 3, current_Time);
            time_Save = current_Time;
        }
    }
    else
    {
        LCD_Print_CenterLine4(NO_CLOCK);
        Setup_Signals_Blinking_Light(NO_CLOCK_LED_Blink, NO_CLOCK_LED_Color);
        date_Save = "";
        time_Save = "";
    }
}
