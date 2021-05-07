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
#include "LIGHTActuator.h"
#include <Arduino.h>
#include "Log.h"

bool LIGHT_Setup()
{
#ifdef LIGHT_SENSOR_ANALOG_PIN    
    if(LIGHT_SENSOR_ANALOG_Setup()) {
        LIGHT_SENSOR_ANALOG_Setup();
        Log("LIGHT sensor analog setup complete");
         return true;          
    }    
#endif    
#ifndef LIGHT_SENSOR_ANALOG_PIN    
    if(LIGHT_SENSOR_DIGITAL_Setup()){
        LIGHT_SENSOR_DIGITAL_Setup();
        Log("LIGHT sensor digital setup complete");
        return true;
    }
#endif    
    Log("LIGHT sensor setup failed");
    return false;
}

#ifdef LIGHT_SENSOR_ANALOG_PIN    
bool LIGHT_SENSOR_ANALOG_Setup()
{
    if(LIGHT_SENSOR_ANALOG_PIN!=-1){
        pinMode(LIGHT_SENSOR_ANALOG_PIN, INPUT);
        return true;
    }
    else {
        return false;
    }    
}
#endif

#ifndef LIGHT_SENSOR_ANALOG_PIN    
bool LIGHT_SENSOR_DIGITAL_Setup()
{
    if(LIGHT_SENSOR_DIGITAL_PIN!=-1){
        pinMode(LIGHT_SENSOR_DIGITAL_PIN, INPUT);
        return true;    
    }
    else {
        return false;
    }
}
#endif

float LIGHT_GET_data()
{
#ifdef LIGHT_SENSOR_ANALOG_PIN    
    if(LIGHT_SENSOR_ANALOG_PIN!=-1){
        return analogRead(LIGHT_SENSOR_ANALOG_PIN) * 0.48 / 100; //Конвертируем уровень аналогового сигнала в Вольты        
    }
#endif

#ifndef LIGHT_SENSOR_ANALOG_PIN    
    if(LIGHT_SENSOR_DIGITAL_PIN!=-1){
        if(digitalRead(LIGHT_SENSOR_DIGITAL_PIN)==HIGH){
            return 1;
        }
        if(digitalRead(LIGHT_SENSOR_DIGITAL_PIN)==LOW){
            return 0;
        }
    }            
#endif    
    return -1;
}
